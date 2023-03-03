/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    6496, 16734, 24384, 39628, 48012, 58714, 37162, 26055, 62902, 39635, 17060, 15553, 33803, 37574, 65245, 13593
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    59584, 52429, 47064, 29580, 4011, 64947, 14685, 37734, 65244, 8452, 23549, 16885, 30058, 49349, 27080, 22434
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8 (*in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8 (*in2, size_t vl);
    vint16m8_t out_v = __riscv_vle16_v_i16m8 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16m8_t __riscv_vse16_v_i16 (int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    59584, 52429, 47064, 29580, 4011, 64947, 14685, 37734, 65244, 8452, 23549, 16885, 30058, 49349, 27080, 22434
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
