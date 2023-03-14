/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    37, 239, 212, 11, 123, 206, 107, 16, 168, 102, 228, 139, 77, 64, 213, 63
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    232, 56, 204, 172, 234, 158, 236, 140, 150, 17, 94, 234, 231, 238, 217, 241
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const uint out_data[] = {
    1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0
    };
    const uint64_t *out = &out_data[0];
    uint32_t masked[] = {
    0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1
    };
    const uint32_t *mask = &masked[0];
    vuint64m2_t data1_v = __riscv_vle64_v_u64m2_m (mask, in1, vl);
    vuint64m2_t data2_v = __riscv_vle64_v_u64m2_m (mask, in2, vl);
    vuint64m2_t out_v = __riscv_vle64_v_u64m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdivu_vx_i64m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m2 (bool64_t mask, uint64_t *out, vuint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    1, 0, 0, 15, 0, 0, 2, 0, 1, 0, 0, 0, 3, 1, 1, 3
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
