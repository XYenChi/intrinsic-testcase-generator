/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    107, 34, -34, 60, 101, -113, -14, -36, -116, 69, -40, 71, -40, -41, 64, -128
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -92, -102, -17, -78, -114, -40, 97, 45, 126, 127, -89, 81, 23, -10, 86, 26
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const int out_data[] = {
    -88, -96, 105, -4, -19, -8, 40, 7, 58, 3, -33, 8, -49, -29, 96, -23
    };
    const int64_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1_m (mask, in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1_m (mask, in2, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m1 (bool64_t mask, int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    18446744073709551528, 18446744073709551548, 105, 18446744073709551612, 18446744073709551603, 18446744073709551463, 40, 9, 58, 196, 18446744073709551487, 8, 18446744073709551567, 18446744073709551565, 96, 18446744073709551514
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
