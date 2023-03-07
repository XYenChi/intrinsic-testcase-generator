/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -26, 51, 15, -102, 12, -8, 96, -25, -63, -78, -47, -18, -19, -90, -46, 53
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -67, 73, 91, 3, -100, 94, -41, -45, -31, -50, 22, -69, 123, 117, 109, -122
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m8(avl);
    const int out_data[] = {
    -68, 116, 49, 114, 105, 42, 118, 45, -66, 66, 106, -60, -37, 81, -73, -107
    };
    const int8_t *out = &out_data[0];
    bool1_t masked[] = {
    0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1
    };
    const bool1_t *mask = &masked[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8_m (mask, *in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8_m (mask, *in2, vl);
    vint8m8_t data1_v = __riscv_vle8_v_i8m8_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i8m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m8 (bool8_t mask, int8_t *out, vint8m8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -68, 117, 50, 114, 105, 43, 119, 46, -66, 66, 106, -60, -36, 82, -73, -106
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
