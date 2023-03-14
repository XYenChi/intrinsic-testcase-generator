/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -44, -2, 65, 56, -12, -106, 57, -89, 29, -114, -39, -86, -15, 40, 2, -126
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    116, -67, -57, -52, -55, 11, 62, -40, 2, -13, -4, 21, -59, -10, -89, 41
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m1(avl);
    const int out_data[] = {
    0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1
    };
    const int16_t *out = &out_data[0];
    uint16_t masked[] = {
    1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0
    };
    const uint16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, in2, vl);
    vint16m1_t out_v = __riscv_vle16_v_i16m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsub_vv_i16m1_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m1 (bool16_t mask, int16_t *out, vint16m1_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    65492, 65, 1, 56, 65524, 65419, 65531, 0, 29, 1, 0, 65450, 1, 0, 91, 1
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
