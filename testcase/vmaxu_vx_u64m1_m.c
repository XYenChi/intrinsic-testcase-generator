/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    246, 144, 18, 102, 237, 219, 26, 206, 197, 98, 165, 25, 91, 248, 134, 118
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    14, 164, 134, 35, 163, 175, 66, 230, 168, 183, 58, 199, 165, 118, 234, 87
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const uint out_data[] = {
    1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0
    };
    const uint64_t *out = &out_data[0];
    uint64_t masked[] = {
    1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1
    };
    const uint64_t *mask = &masked[0];
    vuint64m1_t data1_v = __riscv_vle64_v_u64m1_m (mask, in1, vl);
    vuint64m1_t data2_v = __riscv_vle64_v_u64m1_m (mask, in2, vl);
    vuint64m1_t out_v = __riscv_vle64_v_u64m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_u64m1 (bool64_t mask, uint64_t *out, vuint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    246, 164, 1, 102, 237, 1, 1, 1, 197, 0, 165, 199, 1, 0, 1, 118
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
