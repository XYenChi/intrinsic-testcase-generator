/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    213, 9, 218, 129, 183, 15, 172, 56, 127, 132, 108, 53, 241, 252, 18, 240
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    140, 231, 121, 17, 183, 254, 79, 161, 45, 132, 190, 185, 61, 193, 252, 62
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
        out_v = __riscv_vsub_vx_u64m2 (data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m2 (uint64_t *out, vuint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    73, 18446744073709551394, 97, 112, 0, 18446744073709551377, 93, 18446744073709551511, 82, 0, 18446744073709551534, 18446744073709551484, 180, 59, 18446744073709551382, 178
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
