/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -28, -59, -120, -25, -51, 127, -25, -94, -65, -119, 82, 104, 19, -121, 35, -19
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    46, 24, 90, 7, 84, 126, 31, -97, 105, 13, 108, -109, -73, 109, -26, 69
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1 (in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1 (in2, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i64m1 (data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m1 (int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    18446744073709550328, 18446744073709550200, 18446744073709540816, 18446744073709551441, 18446744073709547332, 16002, 18446744073709550841, 9118, 18446744073709544791, 18446744073709550069, 8856, 18446744073709540280, 18446744073709550229, 18446744073709538427, 18446744073709550706, 18446744073709550305
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
