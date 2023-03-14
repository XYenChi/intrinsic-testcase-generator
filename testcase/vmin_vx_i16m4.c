/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -7, -96, -21, 52, -41, 21, -56, -6, -36, -4, -13, -45, -6, -95, 108, 21
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -13, -57, 40, -88, 34, -57, -127, -102, 65, 41, -117, 87, -46, -22, -119, 108
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4 (in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4 (in2, vl);
    vint16m4_t out_v = __riscv_vle16_v_i16m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i16m4 (data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m4 (int16_t *out, vint16m4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    65529, 65479, 40, 52, 34, 21, 65480, 65530, 65, 41, 65523, 87, 65530, 65514, 108, 108
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
