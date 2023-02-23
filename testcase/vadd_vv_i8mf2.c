/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    211, 18, 149, 24, 242, 38, 36, 114, 77, 52, 203, 21, 167, 41, 83, 52
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    173, 109, 76, 110, 173, 147, 74, 219, 97, 6, 10, 229, 217, 184, 25, 240
    };
    const int8_t *in2 = &data2[0];
    const int8_t out_data[16];
    int8_t *out = &out_data[0];
    vint8mf2_t __riscv_vle8_v_i8mf2 (*in1, vl);
    vint8mf2_t __riscv_vle8_v_i8mf2 (*in2, vl);
    vint8mf2_t __riscv_vle8_v_i8mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint8mf2_t out_data = __riscv_vadd_vv_i8mf2 (data1, data2, vl)
        vint8mf2_t __riscv_vse8_v_i8mf2 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    384, 127, 225, 134, 415, 185, 110, 333, 174, 58, 213, 250, 384, 225, 108, 292
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
