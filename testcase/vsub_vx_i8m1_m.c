/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    33, 95, 117, 238, 127, 239, 53, 165, 66, 120, 168, 94, 246, 136, 135, 48
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    52, 226, 92, 66, 123, 234, 20, 164, 63, 230, 51, 201, 126, 8, 244, 81
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m1(size_t avl);
    const int out_data[] = {
    76, 5, 5, 148, 82, 168, 53, 72, 168, 135, 185, 207, 6, 123, 248, 24
    };
    const int8_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint8m1_t data1_v = __riscv_vle8_v_i8m1_m (mask, *in1, vl);
    vint8m1_t data2_v = __riscv_vle8_v_i8m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u8m1_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse8m1_v_i8 (vbool8_t mask, int8m1_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -19, 5, 25, 148, 4, 5, 53, 1, 3, 135, 185, -107, 120, 128, -109, 24
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
