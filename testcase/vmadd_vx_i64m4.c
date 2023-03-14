/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -1, -124, -16, -2, -59, -19, 39, -79, 20, -111, 112, -97, -54, 67, -53, 10
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    57, 87, -37, -79, -82, -89, 48, 10, 47, -87, -96, -77, 102, -39, 65, -10
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4 (in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4 (in2, vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmadd_vx_i64m4 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m4 (int64_t *out, vint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    57, 87, 18446744073709551579, 18446744073709551535, 18446744073709551534, 18446744073709551527, 87, 18446744073709551547, 67, 18446744073709551418, 16, 18446744073709551442, 48, 18446744073709551577, 65, 0
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
