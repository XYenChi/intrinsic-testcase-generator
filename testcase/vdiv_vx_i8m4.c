/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    251, 53, 212, 129, 117, 55, 139, 86, 228, 215, 128, 172, 223, 199, 125, 12
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    126, 44, 199, 107, 113, 128, 12, 162, 10, 92, 142, 7, 117, 252, 56, 84
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m4(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m4_t data1_v = __riscv_vle8_v_i8m4 (*in1, vl);
    vint8m4_t data2_v = __riscv_vle8_v_i8m4 (*in2, vl);
    vint8m4_t out_v = __riscv_vle8_v_i8m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i8m4 (data1_v, data2_v, vl);
        void vint8m4_t __riscv_vse8_v_i8 (int8m4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    0, 0, 0, 0, 0, 2, 0, 1, 0, 0, 1, 0, 0, 1, 0, 7
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
