/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    55494, 19896, 12051, 29055, 21110, 45966, 7176, 1939, 48769, 2493, 14161, 38684, 26003, 39471, 48866, 12817
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    6662, 35349, 61857, 5612, 2006, 56192, 26657, 44415, 12841, 53984, 58876, 28527, 17253, 33029, 56613, 5633
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    42147, 32840, 54214, 59054, 51700, 61541, 62470, 11386, 54243, 53058, 59217, 41984, 20107, 8413, 22246, 65430
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    2338905619, 653384640, 653332914, 1715813971, 1091387001, 2828793607, 448284721, 22077454, 2645376868, 132273594, 838571938, 1624109057, 522842322, 332069523, 1087073036, 838616310
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
