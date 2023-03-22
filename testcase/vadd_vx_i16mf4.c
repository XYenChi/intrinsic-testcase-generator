/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    62, 73, -77, 51, -14, -27, -40, -6, 81, 20, -79, 46, 86, 58, 46, -52
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    8, 61, 117, 58, 40, -19, 126, 56, -76, -29, -101, -86, 95, -21, -81, 94
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4 (in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4 (in2, vl);
    vint16mf4_t out_v = __riscv_vle16_v_i16mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i16mf4 (data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf4 (int16_t *out, vint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    70, 134, 40, 109, 26, 65490, 86, 50, 5, 65527, 65356, 65496, 181, 37, 65501, 42
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
