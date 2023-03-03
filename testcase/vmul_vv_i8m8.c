/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    115, 30, 22, 11, 225, 176, 74, 76, 228, 162, 252, 195, 22, 107, 223, 132
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    174, 245, 19, 186, 228, 227, 171, 36, 186, 217, 66, 187, 216, 218, 181, 156
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m8(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8 (*in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8 (*in2, vl);
    vint8m8_t out_v = __riscv_vle8_v_i8m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i8m8 (data1_v, data2_v, vl);
        void vint8m8_t __riscv_vse8_v_i8 (int8m8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    20010, 7350, 418, 2046, 51300, 39952, 12654, 2736, 42408, 35154, 16632, 36465, 4752, 23326, 40363, 20592
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
