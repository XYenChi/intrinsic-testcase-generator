/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    18721, 45633, 51102, 58666, 28361, 25075, 32443, 30734, 62442, 38489, 58503, 43256, 37897, 51626, 56112, 64853
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    21480, 29872, 32516, 57199, 57538, 3625, 8492, 21804, 2543, 39885, 3764, 47318, 55373, 47527, 21513, 16331
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    6770, 48650, 47808, 44695, 671, 12258, 38796, 25333, 32165, 20501, 61246, 11421, 25494, 10779, 57189, 9441
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    6770, 48650, 47808, 44695, 671, 12258, 40935, 52538, 64985, 78374, 62267, 90574, 93270, 10779, 57189, 9441
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
