/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    133, 19, 209, 192, 225, 105, 137, 208, 215, 52, 198, 202, 70, 92, 198, 197
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    9, 123, 141, 197, 223, 153, 138, 253, 231, 15, 176, 109, 29, 238, 184, 135
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    uint64_t masked[] = {
    1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1
    };
    const uint64_t *mask = &masked[0];
    vuint64m1_t data1_v = __riscv_vle64_v_u64m1 (in1, vl);
    vuint64m1_t data2_v = __riscv_vle64_v_u64m1 (in2, vl);
    vuint64m1_t out_v = __riscv_vle64_v_u64m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_u64m1 (uint64_t *out, vuint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    143, 143, 351, 390, 449, 258, 276, 461, 446, 67, 374, 311, 99, 330, 383, 333
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
