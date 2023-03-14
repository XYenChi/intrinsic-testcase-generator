/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    245, 107, 43, 144, 232, 171, 130, 216, 14, 144, 209, 251, 49, 195, 209, 89
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    135, 74, 134, 115, 36, 51, 158, 233, 153, 163, 18, 208, 88, 163, 210, 199
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const uint64_t out_data[16];
    const uint64_t *out = &out_data[0];
    vuint64m1_t data1_v = __riscv_vle64_v_u64m1 (in1, vl);
    vuint64m1_t data2_v = __riscv_vle64_v_u64m1 (in2, vl);
    vuint64m1_t out_v = __riscv_vle64_v_u64m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u64m1 (data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m1 (uint64_t *out, vuint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    110, 33, 18446744073709551525, 29, 196, 120, 18446744073709551588, 18446744073709551599, 18446744073709551477, 18446744073709551597, 191, 43, 18446744073709551577, 32, 18446744073709551615, 18446744073709551506
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
