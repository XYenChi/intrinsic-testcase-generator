/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    12034, 14577, 54244, 36776, 47904, 48645, 45422, 39172, 14110, 48918, 7279, 57442, 4996, 35877, 59713, 29024
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    2531, 62920, 16266, 24585, 51812, 50830, 9955, 25536, 3670, 11197, 49790, 13908, 8946, 55838, 29850, 48793
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2 (*in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2 (*in2, vl);
    vint16mf2_t out_v = __riscv_vle16_v_i16mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i16mf2 (data1_v, data2_v, vl);
        void vint16mf2_t __riscv_vse16_v_i16 (int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    12034, 62920, 54244, 36776, 51812, 50830, 45422, 39172, 14110, 48918, 49790, 57442, 8946, 55838, 59713, 48793
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