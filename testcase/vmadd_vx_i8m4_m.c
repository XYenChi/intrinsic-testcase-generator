/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    117, -127, -79, -119, 116, 20, -3, -94, -108, 66, 57, 40, -30, -110, 98, -53
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    78, 45, 60, -79, 83, 71, 79, -7, 77, 119, -3, -79, -17, 33, 121, 5
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m4(avl);
    const int out_data[] = {
    0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1
    };
    const int8_t *out = &out_data[0];
    uint2_t masked[] = {
    1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0
    };
    const uint2_t *mask = &masked[0];
    vint8m4_t data1_v = __riscv_vle8_v_i8m4_m (mask, in1, vl);
    vint8m4_t data2_v = __riscv_vle8_v_i8m4_m (mask, in2, vl);
    vint8m4_t out_v = __riscv_vle8_v_i8m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmadd_vx_i8m4_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m4 (bool8_t mask, int8_t *out, vint8m4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    78, 174, 177, 177, 116, 20, 253, 249, 148, 66, 54, 217, 239, 146, 98, 203
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
