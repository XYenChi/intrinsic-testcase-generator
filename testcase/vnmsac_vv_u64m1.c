/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    162, 57, 70, 225, 171, 96, 105, 174, 197, 44, 105, 197, 71, 116, 234, 63
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    152, 71, 161, 180, 130, 222, 92, 37, 147, 138, 106, 74, 159, 67, 40, 16
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
        out_v = __riscv_vnmsac_vv_u64m1 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m1 (uint64_t *out, vuint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    18446744073709526993, 18446744073709547569, 18446744073709540347, 18446744073709511117, 18446744073709529387, 18446744073709530304, 18446744073709541956, 18446744073709545178, 18446744073709522658, 18446744073709545544, 18446744073709540487, 18446744073709537038, 18446744073709540327, 18446744073709543844, 18446744073709542257, 18446744073709550609
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
