/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    11, 216, 188, 247, 49, 86, 29, 5, 61, 17, 235, 242, 117, 31, 98, 101
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    130, 37, 123, 96, 2, 122, 233, 224, 195, 96, 63, 225, 233, 77, 170, 20
    };
    const int16_t *in2 = &data2[0];
    const int16_t out_data[16];
    int16_t *out = &out_data[0];
    vint16m8_t __riscv_vle16_v_i16m8 (*in1, vl);
    vint16m8_t __riscv_vle16_v_i16m8 (*in2, vl);
    vint16m8_t __riscv_vle16_v_i16m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint16m8_t out_data = __riscv_vadd_vx_i16m8 (data1, data2, vl)
        vint16m8_t __riscv_vse16_v_i16m8 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    141, 253, 311, 343, 51, 208, 262, 229, 256, 113, 298, 467, 350, 108, 268, 121
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
