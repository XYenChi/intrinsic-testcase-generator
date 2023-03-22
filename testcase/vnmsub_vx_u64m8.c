/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    146, 155, 69, 146, 206, 8, 169, 226, 200, 11, 237, 185, 119, 42, 158, 163
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    63, 92, 232, 183, 158, 219, 32, 82, 75, 79, 12, 253, 60, 214, 89, 194
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
        out_v = __riscv_vnmsub_vx_u64m8 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m8 (uint64_t *out, vuint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    83, 155, 18446744073709551453, 146, 206, 18446744073709551405, 169, 226, 125, 18446744073709551548, 237, 18446744073709551548, 59, 18446744073709551444, 158, 163
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
