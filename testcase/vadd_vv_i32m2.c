/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    46, 80, 85, 18, 210, 167, 100, 236, 173, 247, 159, 218, 81, 48, 168, 78
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    137, 22, 223, 100, 88, 159, 230, 239, 27, 10, 40, 226, 237, 200, 112, 68
    };
    const int32_t *in2 = &data2[0];
    const int32_t out_data[16];
    int32_t *out = &out_data[0];
    vint32m2_t __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint32m2_t out_data = __riscv_vadd_vv_i32m2 (data1, data2, vl)
        vint32m2_t __riscv_vse32_v_i32m2 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    183, 102, 308, 118, 298, 326, 330, 475, 200, 257, 199, 444, 318, 248, 280, 146
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
