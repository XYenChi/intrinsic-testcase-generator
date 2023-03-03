/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    31771, 25482, 43336, 32052, 11193, 64605, 42188, 9321, 63224, 4587, 59781, 57823, 46494, 13446, 62843, 47754
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    38680, 38114, 60477, 8884, 17581, 9926, 52782, 6737, 27213, 54643, 1199, 60816, 26359, 7651, 59307, 23865
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    33760, 3483, 35078, 6489, 63305, 31253, 2434, 18710, 24411, 58700, 10197, 37086, 20202, 36169, 10123, 50709
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    38680, 38114, 60477, 6489, 17581, 64605, 2434, 18710, 24411, 58700, 59781, 37086, 46494, 36169, 62843, 50709
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
