/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    12, 231, 47, 18, 144, 120, 99, 130, 183, 42, 120, 196, 151, 28, 200, 114
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    14, 241, 23, 135, 36, 163, 118, 2, 81, 247, 22, 192, 183, 201, 94, 105
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf4(size_t avl);
    const int out_data[] = {
    252, 204, 124, 195, 37, 162, 216, 168, 252, 142, 77, 253, 130, 38, 232, 53
    };
    const int8_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4_m (mask, *in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i8mf4_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse8mf4_v_i8 (vbool8_t mask, int8mf4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    14, 241, 124, 135, 144, 163, 216, 130, 252, 247, 77, 196, 183, 201, 232, 53
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