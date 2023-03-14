/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    55, 213, 129, 185, 47, 142, 92, 150, 255, 211, 103, 213, 138, 162, 26, 127
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    133, 30, 247, 90, 171, 116, 240, 163, 4, 116, 8, 147, 20, 191, 251, 61
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const uint64_t out_data[16];
    const uint64_t *out = &out_data[0];
    vuint64m2_t data1_v = __riscv_vle64_v_u64m2 (in1, vl);
    vuint64m2_t data2_v = __riscv_vle64_v_u64m2 (in2, vl);
    vuint64m2_t out_v = __riscv_vle64_v_u64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrsub_vx_u64m2 (data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m2 (uint64_t *out, vuint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    78, 18446744073709551433, 118, 18446744073709551521, 124, 18446744073709551590, 148, 13, 18446744073709551365, 18446744073709551521, 18446744073709551521, 18446744073709551550, 18446744073709551498, 29, 225, 18446744073709551550
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
