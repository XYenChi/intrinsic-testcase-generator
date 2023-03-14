/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -23, 102, 78, -66, 111, -79, -111, 124, 102, 36, -73, 121, -118, -75, 81, 35
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -104, 118, 37, 90, -127, 63, 46, 124, 51, -8, 78, -21, -108, 87, 75, -121
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf4(avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4 (in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4 (in2, vl);
    vint8mf4_t out_v = __riscv_vle8_v_i8mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vor_vv_i8mf4 (data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf4 (int8_t *out, vint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    249, 118, 111, 254, 239, 191, 191, 124, 119, 252, 255, 251, 158, 247, 91, 167
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
