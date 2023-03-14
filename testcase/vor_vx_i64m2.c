/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -78, -35, -127, -103, -40, 114, 24, 37, 33, 101, 72, 83, 53, -93, 117, -81
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -100, -44, -80, 104, 76, -38, -42, -42, 3, -38, 27, 27, -127, -99, -34, -29
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
        out_v = __riscv_vor_vx_i64m2 (data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m2 (int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    18446744073709551550, 18446744073709551581, 18446744073709551537, 18446744073709551609, 18446744073709551580, 18446744073709551610, 18446744073709551582, 18446744073709551607, 35, 18446744073709551615, 91, 91, 18446744073709551541, 18446744073709551551, 18446744073709551615, 18446744073709551599
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
