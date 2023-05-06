/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    196, 157, 162, 43, 70, 38, 31, 62, 31, 89, 180, 177, 120, 231, 63, 177
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    65, 134, 103, 199, 236, 146, 71, 137, 72, 87, 93, 30, 187, 105, 49, 76
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
        out_v = __riscv_vnmsac_vx_u64m4 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m4 (uint64_t *out, vuint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    18446744073709538877, 18446744073709530578, 18446744073709534931, 18446744073709543059, 18446744073709535097, 18446744073709546068, 18446744073709549416, 18446744073709543123, 18446744073709549385, 18446744073709543873, 18446744073709534876, 18446744073709546306, 18446744073709529176, 18446744073709527361, 18446744073709548530, 18446744073709538164
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
