/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    178, 114, 20, 65, 236, 188, 181, 251, 114, 113, 19, 117, 193, 184, 213, 75
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    202, 215, 136, 143, 80, 140, 17, 144, 168, 22, 133, 101, 176, 118, 39, 230
    };
    const int8_t *in2 = &data2[0];
    const int8_t out_data[16];
    int8_t *out = &out_data[0];
    vint8mf8_t __riscv_vle8_v_i8mf8 (*in1, vl);
    vint8mf8_t __riscv_vle8_v_i8mf8 (*in2, vl);
    vint8mf8_t __riscv_vle8_v_i8mf8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint8mf8_t out_data = __riscv_vadd_vv_i8mf8 (data1, data2, vl)
        vint8mf8_t __riscv_vse8_v_i8mf8 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    380, 329, 156, 208, 316, 328, 198, 395, 282, 135, 152, 218, 369, 302, 252, 305
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
