/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    31, 119, -61, 49, -110, -66, -91, -74, 64, -72, -45, -88, 98, 18, 95, 63
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    40, 21, -63, -103, 74, 9, -124, 62, -60, -57, 48, 127, 116, 59, 117, 114
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8 (in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8 (in2, vl);
    vint16m8_t out_v = __riscv_vle16_v_i16m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_i16m8 (data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m8 (int16_t *out, vint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    65527, 98, 2, 152, 65352, 65461, 33, 65400, 124, 65521, 65443, 65321, 65518, 65495, 65514, 65485
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
