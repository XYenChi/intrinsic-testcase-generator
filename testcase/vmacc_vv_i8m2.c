/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    255, 125, 219, 155, 52, 114, 229, 217, 38, 206, 86, 207, 204, 128, 244, 24
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    249, 131, 227, 153, 49, 143, 192, 90, 92, 146, 100, 29, 105, 181, 119, 14
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m2(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m2_t data1_v = __riscv_vle8_v_i8m2 (*in1, vl);
    vint8m2_t data2_v = __riscv_vle8_v_i8m2 (*in2, vl);
    vint8m2_t out_v = __riscv_vle8_v_i8m2 (*out, vl);
    const int out_data[] = {
    47, 47, 169, 219, 43, 184, 232, 158, 192, 199, 214, 98, 211, 117, 162, 83
    };
    const int8_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i8m2 (data1_v, data2_v, vl);
        void vint8m2_t __riscv_vse8_v_i8 (int8m2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    63542, 16422, 49882, 23934, 2591, 16486, 44200, 19688, 3688, 30275, 8814, 6101, 21631, 23285, 29198, 419
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
