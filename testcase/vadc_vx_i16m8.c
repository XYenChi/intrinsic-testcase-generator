/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    23864, 16034, 10415, 18927, 55310, 52102, 34988, 35300, 34395, 21063, 63124, 61382, 25125, 16437, 32803, 16387
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    52994, 49505, 46684, 19199, 8358, 36214, 60039, 6948, 15780, 18558, 3874, 54936, 64663, 30419, 889, 45500
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
        out_v = __riscv_vadc_vx_i16m8 (data1_v, data2_v, mask, vl);
        void vint16m8_t __riscv_vse16_v_i16 (int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    76858, 65539, 57099, 38126, 63668, 88316, 95027, 42248, 50175, 39621, 66998, 116318, 89788, 46856, 33692, 61887
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
