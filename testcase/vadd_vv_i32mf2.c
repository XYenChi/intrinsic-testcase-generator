/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    232, 223, 168, 2, 115, 122, 92, 56, 138, 168, 121, 9, 66, 58, 67, 198
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    184, 83, 61, 206, 35, 175, 164, 254, 248, 141, 157, 168, 68, 47, 176, 80
    };
    const int32_t *in2 = &data2[0];
    const int32_t out_data[16];
    int32_t *out = &out_data[0];
    vint32mf2_t __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint32mf2_t out_data = __riscv_vadd_vv_i32mf2 (data1, data2, vl)
        vint32mf2_t __riscv_vse32_v_i32mf2 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    416, 306, 229, 208, 150, 297, 256, 310, 386, 309, 278, 177, 134, 105, 243, 278
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
