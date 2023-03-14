/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    199, 45, 188, 167, 169, 3, 164, 203, 118, 183, 5, 209, 103, 233, 215, 8
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    213, 9, 203, 103, 56, 153, 86, 63, 92, 141, 184, 197, 227, 110, 144, 145
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
        out_v = __riscv_vnmsac_vx_u64m1 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m1 (uint64_t *out, vuint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    18446744073709509229, 18446744073709551212, 18446744073709513452, 18446744073709534416, 18446744073709542152, 18446744073709551158, 18446744073709537512, 18446744073709538827, 18446744073709540760, 18446744073709525813, 18446744073709550697, 18446744073709510444, 18446744073709528235, 18446744073709525986, 18446744073709520656, 18446744073709550457
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
