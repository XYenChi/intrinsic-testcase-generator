/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    184, 237, 237, 114, 193, 137, 8, 141, 210, 248, 159, 46, 153, 163, 124, 157
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    164, 10, 131, 45, 225, 161, 229, 103, 183, 59, 255, 247, 108, 249, 114, 221
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m2(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m2_t data1_v = __riscv_vle8_v_i8m2 (*in1, vl);
    vint8m2_t data2_v = __riscv_vle8_v_i8m2 (*in2, vl);
    vint8m2_t out_v = __riscv_vle8_v_i8m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i8m2 (data1_v, data2_v, vl);
        void vint8m2_t __riscv_vse8_v_i8 (int8m2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    348, 247, 368, 159, 418, 298, 237, 244, 393, 307, 414, 293, 261, 412, 238, 378
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
