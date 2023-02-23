/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    146, 198, 242, 1, 142, 71, 138, 231, 186, 212, 78, 25, 168, 147, 91, 118
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    74, 107, 206, 153, 23, 48, 189, 72, 206, 174, 93, 110, 87, 54, 122, 109
    };
    const int16_t *in2 = &data2[0];
    const int16_t out_data[16];
    int16_t *out = &out_data[0];
    vint16m4_t __riscv_vle16_v_i16m4 (*in1, vl);
    vint16m4_t __riscv_vle16_v_i16m4 (*in2, vl);
    vint16m4_t __riscv_vle16_v_i16m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint16m4_t out_data = __riscv_vadd_vx_i16m4 (data1, data2, vl)
        vint16m4_t __riscv_vse16_v_i16m4 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    220, 305, 448, 154, 165, 119, 327, 303, 392, 386, 171, 135, 255, 201, 213, 227
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
