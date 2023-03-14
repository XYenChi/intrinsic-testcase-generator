/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    188, 8, 236, 41, 232, 143, 134, 246, 85, 22, 193, 52, 58, 40, 98, 118
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    68, 106, 92, 115, 6, 242, 106, 7, 179, 122, 78, 18, 38, 86, 54, 91
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const uint out_data[] = {
    0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1
    };
    const uint64_t *out = &out_data[0];
    uint64_t masked[] = {
    0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0
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
    0, 1, 92, 0, 0, 242, 106, 1, 179, 122, 78, 18, 0, 86, 1, 1
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
