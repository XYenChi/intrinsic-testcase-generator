/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    240, 200, 96, 76, 179, 160, 143, 176, 38, 116, 2, 9, 21, 132, 110, 99
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    232, 157, 226, 128, 106, 122, 154, 57, 53, 23, 132, 63, 193, 66, 93, 177
    };
    const int16_t *in2 = &data2[0];
    const int16_t out_data[16];
    int16_t *out = &out_data[0];
    vint16m2_t __riscv_vle16_v_i16m2 (*in1, vl);
    vint16m2_t __riscv_vle16_v_i16m2 (*in2, vl);
    vint16m2_t __riscv_vle16_v_i16m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint16m2_t out_data = __riscv_vadd_vx_i16m2 (data1, data2, vl)
        vint16m2_t __riscv_vse16_v_i16m2 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    472, 357, 322, 204, 285, 282, 297, 233, 91, 139, 134, 72, 214, 198, 203, 276
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
