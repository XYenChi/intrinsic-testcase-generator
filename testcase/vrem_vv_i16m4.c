/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    32378, 55774, 53815, 7472, 18702, 41941, 42657, 7493, 58609, 32379, 34477, 62297, 24693, 46249, 49568, 54212
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    64739, 48758, 39181, 32896, 25821, 51940, 60117, 22895, 51548, 57252, 10685, 54378, 24031, 61920, 16405, 17781
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4 (*in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4 (*in2, vl);
    vint16m4_t out_v = __riscv_vle16_v_i16m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i16m4 (data1_v, data2_v, vl);
        void vint16m4_t __riscv_vse16_v_i16 (int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    32361, 48758, 39181, 3008, 7119, 9999, 17460, 416, 51548, 24873, 10685, 54378, 24031, 15671, 16405, 17781
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
