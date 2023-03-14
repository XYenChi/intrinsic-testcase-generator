/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    4, -85, 112, 34, 36, 38, -86, -91, 40, 118, 37, -111, -115, 97, -127, -119
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -120, 5, 16, 10, -57, -100, 46, -73, -72, 17, 15, -67, 36, 46, 108, -45
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    uint16_t masked[] = {
    1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0
    };
    const uint16_t *mask = &masked[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4 (in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4 (in2, vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m4 (int64_t *out, vint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    -120, -85, 112, 10, -57, -100, 46, -91, 40, 118, 37, -111, -115, 97, 108, -119
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
