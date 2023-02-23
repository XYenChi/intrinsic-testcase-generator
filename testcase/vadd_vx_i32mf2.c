/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    144, 28, 37, 119, 107, 189, 248, 155, 26, 185, 207, 64, 119, 7, 0, 38
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    237, 21, 158, 78, 118, 61, 141, 82, 238, 43, 21, 179, 122, 226, 78, 163
    };
    const int32_t *in2 = &data2[0];
    const int32_t out_data[16];
    int32_t *out = &out_data[0];
    vint32mf2_t __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint32mf2_t out_data = __riscv_vadd_vx_i32mf2 (data1, data2, vl)
        vint32mf2_t __riscv_vse32_v_i32mf2 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    381, 49, 195, 197, 225, 250, 389, 237, 264, 228, 228, 243, 241, 233, 78, 201
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
