/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    168, 219, 126, 18, 40, 78, 248, 101, 244, 118, 216, 166, 163, 126, 43, 251
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    120, 164, 190, 38, 206, 101, 125, 148, 58, 251, 58, 169, 108, 64, 112, 112
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const uint out_data[] = {
    1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0
    };
    const uint64_t *out = &out_data[0];
    uint64_t masked[] = {
    0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1
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
    1, 0, 0, 38, 206, 0, 125, 148, 0, 0, 58, 169, 1, 64, 112, 112
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
