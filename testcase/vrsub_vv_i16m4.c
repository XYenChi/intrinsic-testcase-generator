/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -34, 26, -49, 112, -25, -71, 16, -99, -35, 43, -29, 115, 16, 126, 5, -83
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    14, -62, -85, 111, -58, 120, -47, -7, 0, -95, 2, 54, -1, 62, 104, 124
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4 (in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4 (in2, vl);
    vint16m4_t out_v = __riscv_vle16_v_i16m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrsub_vx_i16m4 (data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m4 (int16_t *out, vint16m4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    48, 65448, 65500, 65535, 65503, 191, 65473, 92, 35, 65398, 31, 65475, 65519, 65472, 99, 207
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
