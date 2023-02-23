/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    117, 209, 235, 77, 228, 128, 200, 190, 248, 45, 123, 137, 126, 144, 183, 249
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    96, 19, 159, 23, 150, 35, 175, 242, 84, 172, 106, 117, 143, 249, 39, 54
    };
    const int16_t *in2 = &data2[0];
    const int16_t out_data[16];
    int16_t *out = &out_data[0];
    vint16mf2_t __riscv_vle16_v_i16mf2 (*in1, vl);
    vint16mf2_t __riscv_vle16_v_i16mf2 (*in2, vl);
    vint16mf2_t __riscv_vle16_v_i16mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint16mf2_t out_data = __riscv_vadd_vv_i16mf2 (data1, data2, vl)
        vint16mf2_t __riscv_vse16_v_i16mf2 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    213, 228, 394, 100, 378, 163, 375, 432, 332, 217, 229, 254, 269, 393, 222, 303
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
