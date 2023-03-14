/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    7, 8, -1, 71, -1, 109, -1, 18, 75, -82, -8, -4, 109, 83, -54, -47
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -114, 82, -29, -101, 55, -63, 71, -19, -127, -65, 4, 74, -23, 100, 69, 105
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
        out_v = __riscv_vmul_vv_i64m8 (data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m8 (int64_t *out, vint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    18446744073709550818, 656, 29, 18446744073709544445, 18446744073709551561, 18446744073709544749, 18446744073709551545, 18446744073709551274, 18446744073709542091, 5330, 18446744073709551584, 18446744073709551320, 18446744073709549109, 8300, 18446744073709547890, 18446744073709546681
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
