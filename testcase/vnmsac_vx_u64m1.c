/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    254, 219, 18, 217, 148, 215, 192, 66, 13, 232, 242, 91, 150, 133, 209, 65
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    135, 103, 244, 16, 123, 10, 106, 241, 16, 46, 5, 153, 159, 204, 43, 253
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
    18446744073709517327, 18446744073709529059, 18446744073709547225, 18446744073709548145, 18446744073709533412, 18446744073709549467, 18446744073709531264, 18446744073709535711, 18446744073709551408, 18446744073709540945, 18446744073709550406, 18446744073709537693, 18446744073709527767, 18446744073709524484, 18446744073709542630, 18446744073709535171
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
