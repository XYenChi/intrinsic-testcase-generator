/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    153, 98, 222, 108, 17, 239, 83, 151, 8, 132, 117, 112, 148, 46, 91, 202
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    19, 141, 4, 158, 14, 9, 116, 219, 161, 112, 172, 63, 107, 87, 140, 134
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
        out_v = __riscv_vsub_vv_u64m8 (data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m8 (uint64_t *out, vuint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    134, 18446744073709551573, 218, 18446744073709551566, 3, 230, 18446744073709551583, 18446744073709551548, 18446744073709551463, 20, 18446744073709551561, 49, 41, 18446744073709551575, 18446744073709551567, 68
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
