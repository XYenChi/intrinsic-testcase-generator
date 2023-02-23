/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    111, 151, 128, 214, 180, 149, 80, 36, 253, 54, 237, 183, 136, 40, 58, 210
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    209, 241, 67, 200, 69, 157, 112, 194, 136, 127, 216, 170, 24, 247, 196, 144
    };
    const int16_t *in2 = &data2[0];
    const int16_t out_data[16];
    int16_t *out = &out_data[0];
    vint16mf2_t __riscv_vle16_v_i16mf2 (*in1, vl);
    vint16mf2_t __riscv_vle16_v_i16mf2 (*in2, vl);
    vint16mf2_t __riscv_vle16_v_i16mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint16mf2_t out_data = __riscv_vadd_vx_i16mf2 (data1, data2, vl)
        vint16mf2_t __riscv_vse16_v_i16mf2 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    320, 392, 195, 414, 249, 306, 192, 230, 389, 181, 453, 353, 160, 287, 254, 354
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
