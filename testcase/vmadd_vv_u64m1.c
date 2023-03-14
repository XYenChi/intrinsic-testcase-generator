/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    61, 212, 234, 238, 25, 6, 31, 245, 211, 40, 123, 34, 208, 239, 251, 54
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    204, 253, 154, 32, 106, 211, 23, 226, 178, 10, 244, 77, 11, 129, 111, 207
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
        out_v = __riscv_vmadd_vv_u64m1 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m1 (uint64_t *out, vuint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    265, 465, 388, 270, 106, 211, 23, 471, 178, 50, 244, 77, 219, 368, 362, 207
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
