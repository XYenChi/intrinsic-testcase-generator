/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -42, 20, 22, -19, -10, 55, 51, -95, -49, -87, 66, -14, -31, -31, -92, 114
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    119, -94, 109, -69, 32, -42, 8, 60, -83, 7, -115, -106, 38, 119, 60, 106
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8 (in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8 (in2, vl);
    vint64m8_t out_v = __riscv_vle64_v_i64m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmadd_vx_i64m8 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m8 (int64_t *out, vint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    77, 18446744073709551522, 109, 18446744073709551528, 32, 18446744073709551574, 59, 60, 18446744073709551533, 18446744073709551536, 18446744073709551567, 18446744073709551496, 7, 119, 18446744073709551584, 106
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
