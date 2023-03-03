/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    231, 18, 106, 67, 236, 102, 90, 230, 171, 215, 55, 230, 64, 148, 63, 35
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    160, 223, 18, 178, 51, 77, 37, 129, 38, 131, 4, 159, 106, 173, 232, 219
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m4(size_t avl);
    const int out_data[] = {
    131, 162, 148, 85, 23, 126, 28, 66, 140, 188, 34, 58, 90, 167, 57, 6
    };
    const int8_t *out = &out_data[0];
    bool2_t masked[] = {
    1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1
    };
    const bool2_t *mask = &masked[0];
    vint8m4_t data1_v = __riscv_vle8_v_i8m4_m (mask, *in1, vl);
    vint8m4_t data2_v = __riscv_vle8_v_i8m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint2_t __riscv_vse8m4_v_i8 (vbool8_t mask, int8m4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    392, 242, 124, 246, 287, 180, 127, 359, 210, 346, 59, 390, 170, 322, 295, 255
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
