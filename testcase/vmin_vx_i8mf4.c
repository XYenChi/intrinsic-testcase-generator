/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    68, 219, 200, 153, 119, 148, 136, 42, 206, 109, 173, 30, 73, 40, 102, 143
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    240, 75, 200, 251, 97, 160, 108, 234, 118, 168, 246, 143, 68, 88, 118, 122
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf4(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4 (*in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4 (*in2, vl);
    vint8mf4_t out_v = __riscv_vle8_v_i8mf4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i8mf4 (data1_v, data2_v, vl);
        void vint8mf4_t __riscv_vse8_v_i8 (int8mf4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    240, 219, 200, 251, 119, 160, 136, 234, 206, 168, 246, 143, 73, 88, 118, 143
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
