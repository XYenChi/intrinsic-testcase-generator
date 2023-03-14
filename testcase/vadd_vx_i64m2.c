/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    81, 73, 116, -58, -100, -66, 57, 46, 29, -66, -89, -5, -93, -15, -77, -109
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -111, -60, 86, 115, 22, -74, 105, 93, 46, -96, 62, -117, 40, 66, 46, 86
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2 (in2, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i64m2 (data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m2 (int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    18446744073709551586, 13, 202, 57, 18446744073709551538, 18446744073709551476, 162, 139, 75, 18446744073709551454, 18446744073709551589, 18446744073709551494, 18446744073709551563, 51, 18446744073709551585, 18446744073709551593
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
