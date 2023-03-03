/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    21486, 10085, 46924, 661, 37751, 26492, 30535, 1514, 56607, 15440, 9290, 30790, 57141, 43544, 5751, 51897
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    31557, 24790, 11233, 32202, 61830, 46286, 18446, 39080, 37189, 48285, 37287, 56090, 8641, 1271, 26510, 24470
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    17381, 39254, 6856, 60693, 54956, 40097, 17151, 58792, 5547, 48134, 50157, 11938, 19857, 53368, 9019, 42806
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    678033702, 250007150, 527097292, 21285522, 54956, 40097, 563248610, 59167120, 5547, 745520400, 50157, 1727011100, 493755381, 55344424, 152459010, 1269919590
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
