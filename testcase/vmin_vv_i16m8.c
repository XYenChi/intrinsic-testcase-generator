/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    58253, 10776, 21194, 54929, 34000, 59026, 24493, 37359, 63955, 3784, 5643, 18468, 45345, 44950, 50018, 28328
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    5902, 1475, 16790, 17504, 61144, 7472, 57693, 13791, 43058, 34963, 37739, 20015, 48204, 35650, 38477, 52258
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8 (*in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8 (*in2, vl);
    vint16m8_t out_v = __riscv_vle16_v_i16m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i16m8 (data1_v, data2_v, vl);
        void vint16m8_t __riscv_vse16_v_i16 (int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    58253, 10776, 21194, 54929, 61144, 59026, 57693, 37359, 63955, 34963, 37739, 20015, 48204, 44950, 50018, 52258
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
