/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    170, 191, 121, 226, 139, 103, 193, 59, 123, 254, 84, 81, 238, 136, 221, 65
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    141, 1, 78, 141, 166, 161, 90, 44, 95, 170, 61, 126, 27, 230, 168, 47
    };
    const int8_t *in2 = &data2[0];
    const int8_t out_data[16];
    int8_t *out = &out_data[0];
    vint8m4_t __riscv_vle8_v_i8m4 (*in1, vl);
    vint8m4_t __riscv_vle8_v_i8m4 (*in2, vl);
    vint8m4_t __riscv_vle8_v_i8m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint8m4_t out_data = __riscv_vadd_vv_i8m4 (data1, data2, vl)
        vint8m4_t __riscv_vse8_v_i8m4 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    311, 192, 199, 367, 305, 264, 283, 103, 218, 424, 145, 207, 265, 366, 389, 112
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
