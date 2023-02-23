/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    36, 56, 8, 151, 17, 18, 106, 189, 90, 159, 187, 89, 140, 142, 193, 91
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    161, 21, 190, 166, 197, 19, 111, 190, 201, 197, 229, 115, 67, 212, 52, 211
    };
    const int8_t *in2 = &data2[0];
    const int8_t out_data[16];
    int8_t *out = &out_data[0];
    vint8m1_t __riscv_vle8_v_i8m1 (*in1, vl);
    vint8m1_t __riscv_vle8_v_i8m1 (*in2, vl);
    vint8m1_t __riscv_vle8_v_i8m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint8m1_t out_data = __riscv_vadd_vv_i8m1 (data1, data2, vl)
        vint8m1_t __riscv_vse8_v_i8m1 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    197, 77, 198, 317, 214, 37, 217, 379, 291, 356, 416, 204, 207, 354, 245, 302
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
