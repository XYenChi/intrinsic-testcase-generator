/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    141, 130, 209, 73, 71, 59, 79, 67, 5, 255, 31, 93, 169, 141, 73, 110
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    37, 233, 22, 181, 221, 38, 222, 237, 191, 40, 31, 243, 65, 145, 234, 120
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const uint out_data[] = {
    1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1
    };
    const uint64_t *out = &out_data[0];
    uint16_t masked[] = {
    1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1
    };
    const uint16_t *mask = &masked[0];
    vuint64m4_t data1_v = __riscv_vle64_v_u64m4_m (mask, in1, vl);
    vuint64m4_t data2_v = __riscv_vle64_v_u64m4_m (mask, in2, vl);
    vuint64m4_t out_v = __riscv_vle64_v_u64m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vxor_vx_u64m4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m4 (bool64_t mask, uint64_t *out, vuint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1
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