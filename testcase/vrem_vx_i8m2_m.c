/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    192, 57, 59, 158, 185, 143, 239, 153, 178, 222, 112, 56, 214, 189, 46, 226
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    231, 240, 71, 79, 204, 122, 0, 36, 10, 39, 221, 21, 171, 211, 198, 122
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m2(size_t avl);
    const int out_data[] = {
    132, 2, 166, 49, 53, 54, 176, 117, 199, 126, 136, 195, 126, 102, 208, 188
    };
    const int8_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint8m2_t data1_v = __riscv_vle8_v_i8m2_m (mask, *in1, vl);
    vint8m2_t data2_v = __riscv_vle8_v_i8m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i8m2_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse8m2_v_i8 (vbool8_t mask, int8m2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    39, 12, 166, 79, 53, 54, 0, 36, 199, 126, 109, 21, 171, 22, 14, 122
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
