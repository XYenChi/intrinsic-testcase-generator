/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    192, 150, 198, 120, 127, 61, 205, 42, 80, 110, 160, 96, 129, 18, 103, 7
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    122, 247, 88, 53, 150, 106, 180, 37, 107, 123, 23, 123, 26, 172, 192, 236
    };
    const int32_t *in2 = &data2[0];
    const int32_t out_data[16];
    int32_t *out = &out_data[0];
    vint32m8_t __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint32m8_t out_data = __riscv_vadd_vv_i32m8 (data1, data2, vl)
        vint32m8_t __riscv_vse32_v_i32m8 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    314, 397, 286, 173, 277, 167, 385, 79, 187, 233, 183, 219, 155, 190, 295, 243
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
