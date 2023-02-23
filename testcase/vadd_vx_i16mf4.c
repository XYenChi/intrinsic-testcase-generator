/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    82, 18, 118, 173, 56, 112, 85, 125, 168, 155, 120, 159, 180, 247, 204, 141
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    137, 222, 118, 152, 187, 1, 116, 74, 238, 200, 123, 161, 99, 160, 249, 6
    };
    const int16_t *in2 = &data2[0];
    const int16_t out_data[16];
    int16_t *out = &out_data[0];
    vint16mf4_t __riscv_vle16_v_i16mf4 (*in1, vl);
    vint16mf4_t __riscv_vle16_v_i16mf4 (*in2, vl);
    vint16mf4_t __riscv_vle16_v_i16mf4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint16mf4_t out_data = __riscv_vadd_vx_i16mf4 (data1, data2, vl)
        vint16mf4_t __riscv_vse16_v_i16mf4 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    219, 240, 236, 325, 243, 113, 201, 199, 406, 355, 243, 320, 279, 407, 453, 147
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
