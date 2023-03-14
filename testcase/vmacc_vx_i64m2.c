/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    34, 65, -110, 5, -34, 2, 18, -64, 80, -48, -5, -73, 46, -70, -122, -64
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    93, -92, 17, 75, -86, -100, -49, 93, 28, -54, 65, 93, 24, -128, 52, 44
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
        out_v = __riscv_vmacc_vx_i64m2 (data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m2 (int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    3163, 18446744073709545637, 18446744073709549747, 376, 2924, 18446744073709551416, 18446744073709550734, 18446744073709545664, 2240, 2592, 18446744073709551292, 18446744073709544828, 1105, 8961, 18446744073709545272, 18446744073709548800
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
