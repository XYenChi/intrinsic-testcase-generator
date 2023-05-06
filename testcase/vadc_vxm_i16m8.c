/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    119, 21, 62, -74, 21, -3, -56, -117, 32, 26, -96, 0, 119, 97, 14, -119
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -107, 86, -44, 74, -48, 114, -75, -22, -51, 80, -98, -94, -123, -67, -80, -23
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    uint2_t masked[] = {
    0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1
    };
    const uint2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8 (in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8 (in2, vl);
    vint16m8_t out_v = __riscv_vle16_v_i16m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vxm_i16m8 (data1_v, data2_v, masked, vl);
        void __riscv_vse16_v_i16m8 (int16_t *out, vint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    12, 107, 18, 1, -27, 112, -131, -139, -18, 106, -194, -93, -3, 30, -66, -141
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
