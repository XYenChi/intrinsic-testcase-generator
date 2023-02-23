/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    159, 35, 30, 248, 38, 186, 66, 19, 61, 246, 235, 77, 56, 23, 7, 14
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    8, 245, 56, 139, 60, 106, 37, 246, 191, 38, 252, 212, 4, 113, 30, 27
    };
    const int8_t *in2 = &data2[0];
    const int8_t out_data[16];
    int8_t *out = &out_data[0];
    vint8m2_t __riscv_vle8_v_i8m2 (*in1, vl);
    vint8m2_t __riscv_vle8_v_i8m2 (*in2, vl);
    vint8m2_t __riscv_vle8_v_i8m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint8m2_t out_data = __riscv_vadd_vx_i8m2 (data1, data2, vl)
        vint8m2_t __riscv_vse8_v_i8m2 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    167, 280, 86, 387, 98, 292, 103, 265, 252, 284, 487, 289, 60, 136, 37, 41
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
