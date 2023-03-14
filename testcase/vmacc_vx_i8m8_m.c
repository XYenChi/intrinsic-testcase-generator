/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -30, 90, 122, -35, -61, -6, -66, -10, -126, -48, -33, -81, 27, -30, 96, -104
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    81, -86, -51, -106, 62, -121, -43, -99, -65, -114, -55, 113, -83, 122, -83, 104
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m8(avl);
    const int out_data[] = {
    1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1
    };
    const int8_t *out = &out_data[0];
    uint1_t masked[] = {
    0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0
    };
    const uint1_t *mask = &masked[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8_m (mask, in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8_m (mask, in2, vl);
    vint8m8_t out_v = __riscv_vle8_v_i8m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i8m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m8 (bool8_t mask, int8_t *out, vint8m8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    1, 196, 179, 127, 1, 214, 22, 223, 254, 96, 1, 64, 64, 180, 1, 1
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
