/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    129, 101, 250, 243, 179, 236, 199, 241, 106, 6, 47, 193, 62, 174, 118, 251
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    241, 173, 37, 169, 130, 49, 20, 206, 94, 252, 223, 120, 233, 143, 104, 233
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
        out_v = __riscv_vnmsac_vv_u64m2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m2 (uint64_t *out, vuint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    18446744073709520527, 18446744073709534143, 18446744073709542367, 18446744073709510549, 18446744073709528346, 18446744073709540053, 18446744073709547637, 18446744073709501971, 18446744073709541653, 18446744073709550105, 18446744073709541135, 18446744073709528456, 18446744073709537170, 18446744073709526734, 18446744073709539344, 18446744073709493133
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
