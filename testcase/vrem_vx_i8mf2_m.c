/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    70, 89, 99, 70, 45, 54, 6, 256, 171, 85, 13, 1, 7, 56, 63, 97
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    113, 143, 143, 168, 150, 54, 0, 84, 255, 118, 116, 64, 251, 153, 240, 236
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf2(size_t avl);
    const int out_data[] = {
    132, 200, 67, 47, 108, 203, 125, 40, 112, 159, 12, 227, 29, 222, 122, 39
    };
    const int8_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2_m (mask, *in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i8mf2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse8mf2_v_i8 (vbool8_t mask, int8mf2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    43, 200, 67, 47, 15, 203, 0, 40, 84, 33, 12, 227, 6, 222, 122, 42
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
