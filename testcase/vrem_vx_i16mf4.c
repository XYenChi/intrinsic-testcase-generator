/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    6221, 18195, 30406, 55782, 38267, 40786, 2529, 10117, 9034, 53830, 40644, 54440, 34871, 30723, 10446, 48128
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    34227, 51599, 36527, 20273, 56843, 13314, 34048, 5552, 27915, 42757, 19566, 46259, 51970, 65215, 8453, 5823
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4 (*in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4 (*in2, vl);
    vint16mf4_t out_v = __riscv_vle16_v_i16mf4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i16mf4 (data1_v, data2_v, vl);
        void vint16mf4_t __riscv_vse16_v_i16 (int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    3122, 15209, 6121, 20273, 18576, 13314, 1171, 5552, 813, 42757, 19566, 46259, 17099, 3769, 8453, 5823
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
