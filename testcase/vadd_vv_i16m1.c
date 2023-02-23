/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    138, 144, 205, 158, 86, 204, 252, 248, 18, 221, 29, 45, 180, 191, 131, 6
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    217, 120, 152, 66, 91, 103, 85, 4, 243, 20, 49, 184, 82, 47, 158, 23
    };
    const int16_t *in2 = &data2[0];
    const int16_t out_data[16];
    int16_t *out = &out_data[0];
    vint16m1_t __riscv_vle16_v_i16m1 (*in1, vl);
    vint16m1_t __riscv_vle16_v_i16m1 (*in2, vl);
    vint16m1_t __riscv_vle16_v_i16m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint16m1_t out_data = __riscv_vadd_vv_i16m1 (data1, data2, vl)
        vint16m1_t __riscv_vse16_v_i16m1 (out, out_data, vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    355, 264, 357, 224, 177, 307, 337, 252, 261, 241, 78, 229, 262, 238, 289, 29
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
