/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    90, 92, 17, -60, -112, 109, 2, 26, -68, -78, -115, 86, -39, 100, 120, 104
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -88, 98, -111, 109, 96, 33, -119, -35, 85, 78, -110, 5, -20, 5, 84, 61
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
        out_v = __riscv_vsub_vx_i8mf4 (data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf4 (int8_t *out, vint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    127, -6, 127, -128, -128, 76, 121, 61, -128, -128, -5, 81, -19, 95, 36, 43
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
