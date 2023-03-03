/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    213, 44, 182, 242, 3, 125, 36, 241, 118, 9, 158, 83, 218, 65, 157, 242
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    229, 208, 256, 197, 226, 114, 239, 170, 81, 162, 56, 138, 35, 168, 97, 43
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf4(size_t avl);
    const int out_data[] = {
    98, 238, 44, 126, 222, 166, 30, 82, 78, 170, 209, 124, 208, 236, 246, 102
    };
    const int8_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4_m (mask, *in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i8mf4_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse8mf4_v_i8 (vbool8_t mask, int8mf4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    98, 238, 74, 197, 222, 166, 23, 82, 81, 170, 209, 55, 208, 38, 246, 43
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
