/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    73, 24, 235, 192, 158, 41, 173, 138, 254, 166, 122, 106, 23, 3, 192, 59
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    62, 83, 178, 69, 132, 129, 107, 122, 148, 177, 141, 13, 246, 175, 171, 80
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m2(size_t avl);
    const int out_data[] = {
    8, 168, 15, 244, 137, 205, 245, 46, 86, 186, 187, 71, 178, 132, 252, 36
    };
    const int8_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint8m2_t data1_v = __riscv_vle8_v_i8m2_m (mask, *in1, vl);
    vint8m2_t data2_v = __riscv_vle8_v_i8m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint4_t __riscv_vse8m2_v_i8 (vbool8_t mask, int8m2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    135, 107, 413, 262, 290, 171, 281, 260, 403, 344, 263, 119, 270, 179, 364, 140
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
