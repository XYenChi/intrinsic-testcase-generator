/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    168, 137, 244, 146, 102, 157, 68, 146, 203, 66, 167, 223, 133, 46, 199, 19
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    98, 113, 241, 96, 2, 235, 188, 228, 48, 230, 160, 251, 107, 34, 114, 244
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const uint out_data[] = {
    1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };
    const uint64_t *out = &out_data[0];
    uint8_t masked[] = {
    1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0
    };
    const uint8_t *mask = &masked[0];
    vuint64m8_t data1_v = __riscv_vle64_v_u64m8_m (mask, in1, vl);
    vuint64m8_t data2_v = __riscv_vle64_v_u64m8_m (mask, in2, vl);
    vuint64m8_t out_v = __riscv_vle64_v_u64m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i64m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m8 (bool64_t mask, uint64_t *out, vuint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    16464, 0, 0, 14016, 0, 0, 0, 33288, 1, 1, 26720, 1, 1, 1, 1, 1
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
