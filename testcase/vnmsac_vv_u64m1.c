/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    108, 90, 67, 73, 166, 149, 60, 104, 216, 39, 17, 252, 231, 76, 201, 152
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    0, 178, 227, 67, 136, 107, 33, 241, 15, 246, 124, 202, 87, 110, 50, 127
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
    0, 18446744073709535597, 18446744073709536408, 18446744073709546726, 18446744073709529040, 18446744073709535673, 18446744073709549637, 18446744073709526553, 18446744073709548376, 18446744073709542023, 18446744073709549509, 18446744073709500713, 18446744073709531519, 18446744073709543257, 18446744073709541566, 18446744073709532312
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
