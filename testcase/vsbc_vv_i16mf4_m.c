/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    49348, 16529, 49351, 29616, 1519, 33605, 37983, 49672, 16380, 23783, 64265, 16913, 35685, 63065, 16674, 34212
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    3379, 11956, 38752, 55990, 10265, 43251, 50380, 46588, 41134, 36033, 35604, 42843, 42596, 6545, 33354, 41649
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    45817, 8530, 17341, 57599, 43476, 15480, 47496, 30494, 53273, 53667, 44880, 58901, 15272, 39205, 21884, 19507
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    45969, 4572, 10599, -26374, -8747, -9647, -12397, 3084, -24755, -12250, 28661, -25930, -6911, 56519, -16680, -7438
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
