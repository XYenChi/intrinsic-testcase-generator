/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    41344, 3241, 1290, 105, 16750, 16085, 50046, 39374, 15281, 5062, 44812, 61941, 7057, 59375, 52740, 17043
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    42872, 37271, 227, 16157, 54840, 20450, 6120, 47515, 19242, 37438, 13652, 17001, 16400, 24045, 60415, 8223
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1 (*in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1 (*in2, size_t vl);
    vint16m1_t out_v = __riscv_vle16_v_i16m1 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16m1_t __riscv_vse16_v_i16 (int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    42872, 37271, 227, 16157, 54840, 20450, 6120, 47515, 19242, 37438, 13652, 17001, 16400, 24045, 60415, 8223
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
