/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    104, 153, 170, 49, 30, 235, 110, 148, 135, 149, 251, 69, 55, 186, 43, 159
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    177, 188, 82, 149, 253, 62, 206, 68, 72, 0, 161, 133, 117, 186, 113, 12
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const uint64_t out_data[16];
    const uint64_t *out = &out_data[0];
    vuint64m8_t data1_v = __riscv_vle64_v_u64m8 (in1, vl);
    vuint64m8_t data2_v = __riscv_vle64_v_u64m8 (in2, vl);
    vuint64m8_t out_v = __riscv_vle64_v_u64m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vv_u64m8 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m8 (uint64_t *out, vuint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    18446744073709533208, 18446744073709522852, 18446744073709537677, 18446744073709544315, 18446744073709544027, 18446744073709537047, 18446744073709528957, 18446744073709541552, 18446744073709541896, 0, 18446744073709511206, 18446744073709542439, 18446744073709545181, 18446744073709517021, 18446744073709546757, 18446744073709549709
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
