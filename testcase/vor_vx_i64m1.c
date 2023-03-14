/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -95, -5, -93, 39, -29, 36, 87, 47, -96, 28, 40, -46, 47, -86, -92, -41
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -32, -109, 113, -126, 111, -31, 80, 65, 98, -79, -84, -117, 105, 25, -83, 15
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
        out_v = __riscv_vor_vx_i64m1 (data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m1 (int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    18446744073709551585, 18446744073709551611, 18446744073709551603, 18446744073709551527, 18446744073709551599, 18446744073709551589, 87, 111, 18446744073709551586, 18446744073709551549, 18446744073709551532, 18446744073709551579, 111, 18446744073709551547, 18446744073709551533, 18446744073709551583
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
