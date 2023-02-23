/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    131, 89, 7, 63, 131, 181, 136, 253, 127, 169, 50, 79, 145, 124, 224, 104
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    179, 139, 183, 234, 152, 94, 183, 193, 162, 80, 232, 6, 91, 32, 44, 139
    };
    const int32_t *in2 = &data2[0];
    const int32_t out_data[16];
    int32_t *out = &out_data[0];
    vint32m4_t __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t __riscv_vle32_v_i32m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint32m4_t out_data = __riscv_vadd_vv_i32m4 (data1, data2, vl)
        vint32m4_t __riscv_vse32_v_i32m4 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    310, 228, 190, 297, 283, 275, 319, 446, 289, 249, 282, 85, 236, 156, 268, 243
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
