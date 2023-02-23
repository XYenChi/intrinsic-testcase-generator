/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    77, 45, 9, 56, 112, 173, 168, 230, 101, 182, 155, 32, 76, 87, 86, 248
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    217, 241, 215, 52, 249, 101, 45, 46, 81, 169, 59, 127, 239, 166, 244, 110
    };
    const int16_t *in2 = &data2[0];
    const int16_t out_data[16];
    int16_t *out = &out_data[0];
    vint16mf4_t __riscv_vle16_v_i16mf4 (*in1, vl);
    vint16mf4_t __riscv_vle16_v_i16mf4 (*in2, vl);
    vint16mf4_t __riscv_vle16_v_i16mf4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint16mf4_t out_data = __riscv_vadd_vv_i16mf4 (data1, data2, vl)
        vint16mf4_t __riscv_vse16_v_i16mf4 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    294, 286, 224, 108, 361, 274, 213, 276, 182, 351, 214, 159, 315, 253, 330, 358
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
