/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    221, 219, 32, 92, 150, 46, 103, 23, 247, 36, 201, 104, 227, 180, 210, 71
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    237, 76, 172, 244, 39, 19, 237, 131, 135, 247, 139, 130, 222, 112, 248, 231
    };
    const int16_t *in2 = &data2[0];
    const int16_t out_data[16];
    int16_t *out = &out_data[0];
    vint16m2_t __riscv_vle16_v_i16m2 (*in1, vl);
    vint16m2_t __riscv_vle16_v_i16m2 (*in2, vl);
    vint16m2_t __riscv_vle16_v_i16m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint16m2_t out_data = __riscv_vadd_vv_i16m2 (data1, data2, vl)
        vint16m2_t __riscv_vse16_v_i16m2 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    458, 295, 204, 336, 189, 65, 340, 154, 382, 283, 340, 234, 449, 292, 458, 302
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
