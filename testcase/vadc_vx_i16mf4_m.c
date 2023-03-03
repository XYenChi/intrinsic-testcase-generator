/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    11172, 15981, 45767, 36328, 5088, 27402, 61018, 29626, 60027, 20664, 63513, 7000, 28375, 3212, 56721, 1265
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    10364, 28426, 41798, 60231, 34662, 14676, 24415, 22460, 40966, 25371, 40598, 44650, 36061, 14505, 61948, 8289
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    23989, 32748, 3340, 43511, 19374, 62454, 40975, 63679, 15812, 45707, 57410, 55521, 61796, 33057, 12454, 61390
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    21537, 44407, 87565, 96559, 39751, 42078, 85433, 52086, 100993, 46035, 104112, 51650, 64436, 17718, 118670, 9554
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
