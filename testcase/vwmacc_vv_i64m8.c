/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    30, 88, -5, -62, 62, 33, -106, -73, 11, 93, -122, -13, -100, 13, 19, -63
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -57, 41, 30, 121, -17, -70, -75, -61, -28, -79, 24, -76, 84, -6, -82, -78
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
        out_v = __riscv_vwmacc_vv_i64m8 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m8 (int64_t *out, vint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    18446744073709549907, 3608, 18446744073709551466, 18446744073709544114, 18446744073709550563, 18446744073709549306, 7951, 4454, 18446744073709551309, 18446744073709544270, 18446744073709548689, 988, 18446744073709543216, 18446744073709551538, 18446744073709550059, 4914
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
