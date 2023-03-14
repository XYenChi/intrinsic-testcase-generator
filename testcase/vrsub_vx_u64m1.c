/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    93, 120, 94, 75, 3, 168, 243, 102, 170, 221, 136, 243, 231, 34, 97, 138
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    74, 218, 166, 56, 25, 27, 85, 56, 162, 69, 65, 116, 146, 39, 208, 146
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
        out_v = __riscv_vrsub_vx_u64m1 (data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m1 (uint64_t *out, vuint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    18446744073709551597, 98, 72, 18446744073709551597, 22, 18446744073709551475, 18446744073709551458, 18446744073709551570, 18446744073709551608, 18446744073709551464, 18446744073709551545, 18446744073709551489, 18446744073709551531, 5, 111, 8
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
