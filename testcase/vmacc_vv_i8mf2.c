/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    104, 119, 10, 152, 147, 136, 19, 177, 219, 229, 47, 211, 142, 80, 17, 152
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    69, 99, 26, 235, 162, 251, 227, 187, 255, 213, 247, 140, 41, 110, 185, 110
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf2(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2 (*in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2 (*in2, vl);
    vint8mf2_t out_v = __riscv_vle8_v_i8mf2 (*out, vl);
    const int out_data[] = {
    14, 53, 72, 91, 208, 52, 136, 207, 133, 221, 33, 138, 98, 46, 234, 193
    };
    const int8_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i8mf2 (data1_v, data2_v, vl);
        void vint8mf2_t __riscv_vse8_v_i8 (int8mf2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    7190, 11834, 332, 35811, 24022, 34188, 4449, 33306, 55978, 48998, 11642, 29678, 5920, 8846, 3379, 16913
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
