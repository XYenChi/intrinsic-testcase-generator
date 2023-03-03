/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    211, 234, 124, 250, 60, 17, 58, 247, 102, 14, 115, 223, 129, 137, 106, 191
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    168, 160, 110, 142, 67, 173, 106, 88, 115, 19, 227, 165, 171, 170, 254, 171
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m4(size_t avl);
    const int out_data[] = {
    64, 30, 143, 196, 41, 117, 247, 114, 92, 246, 118, 223, 0, 65, 11, 69
    };
    const int8_t *out = &out_data[0];
    bool2_t masked[] = {
    1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0
    };
    const bool2_t *mask = &masked[0];
    vint8m4_t data1_v = __riscv_vle8_v_i8m4_m (mask, *in1, vl);
    vint8m4_t data2_v = __riscv_vle8_v_i8m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u8m4_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse8m4_v_i8 (vbool8_t mask, int8m4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    43, 30, 14, 108, -7, -156, -48, 114, 92, -5, 118, 58, -42, 65, -148, 69
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
