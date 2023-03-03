/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    156, 20, 187, 59, 37, 228, 105, 101, 128, 89, 86, 71, 114, 158, 151, 112
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    226, 132, 33, 45, 30, 39, 81, 176, 83, 184, 237, 243, 22, 18, 98, 143
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m1(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m1_t data1_v = __riscv_vle8_v_i8m1 (*in1, vl);
    vint8m1_t data2_v = __riscv_vle8_v_i8m1 (*in2, vl);
    vint8m1_t out_v = __riscv_vle8_v_i8m1 (*out, vl);
    const int out_data[] = {
    100, 189, 146, 67, 21, 105, 222, 177, 66, 66, 146, 52, 32, 169, 137, 163
    };
    const int8_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i8m1 (data1_v, data2_v, vl);
        void vint8m1_t __riscv_vse8_v_i8 (int8m1_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    35356, 2829, 6317, 2722, 1131, 8997, 8727, 17953, 10690, 16442, 20528, 17305, 2540, 3013, 14935, 16179
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
