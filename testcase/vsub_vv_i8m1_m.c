/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    134, 2, 70, 93, 208, 88, 157, 141, 59, 225, 210, 207, 207, 18, 138, 5
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    19, 205, 90, 201, 165, 4, 13, 87, 191, 191, 39, 105, 154, 123, 16, 126
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m1(size_t avl);
    const int out_data[] = {
    162, 33, 192, 28, 23, 70, 247, 2, 74, 8, 214, 185, 74, 91, 138, 153
    };
    const int8_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint8m1_t data1_v = __riscv_vle8_v_i8m1_m (mask, *in1, vl);
    vint8m1_t data2_v = __riscv_vle8_v_i8m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u8m1_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse8m1_v_i8 (vbool8_t mask, int8m1_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    115, -203, -20, 28, 23, 84, 247, 2, 74, 8, 214, 185, 74, 91, 122, 153
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
