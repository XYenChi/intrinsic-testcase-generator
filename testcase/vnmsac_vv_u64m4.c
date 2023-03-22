/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    56, 248, 42, 45, 82, 154, 246, 7, 86, 76, 250, 241, 109, 252, 101, 33
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    156, 153, 180, 234, 160, 177, 207, 116, 222, 57, 73, 77, 14, 66, 188, 187
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const uint64_t out_data[16];
    const uint64_t *out = &out_data[0];
    vuint64m4_t data1_v = __riscv_vle64_v_u64m4 (in1, vl);
    vuint64m4_t data2_v = __riscv_vle64_v_u64m4 (in2, vl);
    vuint64m4_t out_v = __riscv_vle64_v_u64m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vv_u64m4 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m4 (uint64_t *out, vuint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    18446744073709542880, 18446744073709513672, 18446744073709544056, 18446744073709541087, 18446744073709538497, 18446744073709524358, 18446744073709500695, 18446744073709550804, 18446744073709532525, 18446744073709547284, 18446744073709533367, 18446744073709533059, 18446744073709550091, 18446744073709534984, 18446744073709532629, 18446744073709545446
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
