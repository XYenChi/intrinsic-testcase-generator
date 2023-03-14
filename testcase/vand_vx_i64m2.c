/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -101, 104, 1, -108, -56, 60, 89, 34, 23, 115, -101, -120, 99, -60, 92, 44
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -121, 18, -26, -89, -10, 77, 78, -90, -127, -90, -69, 74, 125, 10, -58, -46
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
        void __riscv_vse64_v_i64m2 (int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    18446744073709551495, 18, 18446744073709551590, 18446744073709551527, 18446744073709551606, 77, 78, 18446744073709551526, 18446744073709551489, 18446744073709551526, 18446744073709551547, 74, 125, 10, 18446744073709551558, 18446744073709551570
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
