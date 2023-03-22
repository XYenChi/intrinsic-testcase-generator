/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    50, -93, 53, -114, -32, 97, 75, 7, -41, 9, -77, 96, -79, 84, 74, -66
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -110, -49, -50, -88, -30, -9, -24, -61, -80, 38, 91, 15, -22, -95, -124, 55
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
        out_v = __riscv_vwmacc_vx_i64m2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m2 (int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    18446744073709546116, 4557, 18446744073709548967, 10033, 961, 18446744073709550744, 18446744073709549816, 18446744073709551190, 3280, 343, 18446744073709544609, 1441, 1739, 18446744073709543637, 18446744073709542440, 18446744073709547986
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
