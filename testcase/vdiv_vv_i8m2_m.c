/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    171, 243, 70, 99, 208, 168, 245, 64, 22, 81, 177, 67, 162, 78, 3, 25
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    171, 192, 1, 60, 83, 189, 136, 85, 125, 28, 122, 245, 101, 198, 170, 128
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m2(size_t avl);
    const int out_data[] = {
    23, 223, 7, 222, 176, 18, 59, 251, 60, 255, 240, 173, 173, 98, 205, 177
    };
    const int8_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vint8m2_t data1_v = __riscv_vle8_v_i8m2_m (mask, *in1, vl);
    vint8m2_t data2_v = __riscv_vle8_v_i8m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vv_i8m2_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse8m2_v_i8 (vbool8_t mask, int8m2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    23, 223, 0, 222, 0, 1, 0, 1, 5, 255, 0, 3, 0, 98, 205, 177
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
