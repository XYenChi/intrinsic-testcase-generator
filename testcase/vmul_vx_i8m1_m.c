/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    139, 117, 72, 107, 196, 200, 247, 16, 172, 118, 146, 22, 24, 161, 93, 6
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    219, 252, 159, 242, 204, 118, 96, 63, 240, 94, 219, 211, 176, 21, 195, 43
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m1(size_t avl);
    const int out_data[] = {
    214, 151, 100, 174, 9, 49, 73, 90, 60, 55, 211, 31, 33, 190, 26, 248
    };
    const int8_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint8m1_t data1_v = __riscv_vle8_v_i8m1_m (mask, *in1, vl);
    vint8m1_t data2_v = __riscv_vle8_v_i8m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i8m1_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse8m1_v_i8 (vbool8_t mask, int8m1_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    214, 29484, 11448, 174, 39984, 49, 73, 90, 60, 11092, 31974, 4642, 4224, 3381, 18135, 258
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
