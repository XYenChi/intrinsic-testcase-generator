/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    61, 169, 252, 40, 253, 78, 69, 92, 22, 123, 159, 119, 7, 170, 137, 102
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    225, 171, 74, 6, 40, 246, 213, 54, 18, 217, 214, 221, 39, 200, 117, 133
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
        out_v = __riscv_vnmsac_vx_u64m8 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m8 (uint64_t *out, vuint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    18446744073709537892, 18446744073709522717, 18446744073709532969, 18446744073709551377, 18446744073709541497, 18446744073709532428, 18446744073709536919, 18446744073709546648, 18446744073709551220, 18446744073709524925, 18446744073709517590, 18446744073709525318, 18446744073709551343, 18446744073709517616, 18446744073709535588, 18446744073709538051
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
