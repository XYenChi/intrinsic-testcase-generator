/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    20910, 44327, 23996, 62173, 13359, 5796, 4559, 41919, 45581, 32174, 23567, 48009, 15882, 36900, 10455, 45227
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    35652, 36139, 1063, 5044, 19492, 59015, 50384, 59795, 37635, 15634, 61188, 35923, 39685, 51116, 58130, 50061
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
        out_v = __riscv_vadd_vx_i16mf2 (data1_v, data2_v, vl);
        void vint16mf2_t __riscv_vse16_v_i16 (int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    56562, 80466, 25059, 67217, 32851, 64811, 54943, 101714, 83216, 47808, 84755, 83932, 55567, 88016, 68585, 95288
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
