/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    95, 107, 1, 244, 126, 87, 39, 25, 201, 217, 35, 136, 82, 190, 65, 168
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    238, 102, 83, 135, 193, 49, 97, 136, 241, 110, 51, 23, 31, 199, 32, 124
    };
    const int8_t *in2 = &data2[0];
    const int8_t out_data[16];
    int8_t *out = &out_data[0];
    vint8m4_t __riscv_vle8_v_i8m4 (*in1, vl);
    vint8m4_t __riscv_vle8_v_i8m4 (*in2, vl);
    vint8m4_t __riscv_vle8_v_i8m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint8m4_t out_data = __riscv_vadd_vx_i8m4 (data1, data2, vl)
        vint8m4_t __riscv_vse8_v_i8m4 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    333, 209, 84, 379, 319, 136, 136, 161, 442, 327, 86, 159, 113, 389, 97, 292
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
