/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -30718, -25586, -12197, 29210, 5057, -10264, 27211, -31834, 29986, 32494, -565, -11564, 4154, 32401, -15664, 4868
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    18773, 9434, 5, 12844, 5781, 3230, -16719, 26039, 28243, 32116, 12868, -11462, -3931, -12890, 124, 17214
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2 (*in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2 (*in2, vl);
    vint16m2_t out_v = __riscv_vle16_v_i16m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u16m2 (data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m2 (int16_t *out, vint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    -38833, -41268, 18126, 9926, -14884, 7070, 31475, -39599, 19978, 15220, 8601, -34854, -6675, 26329, -5173, -7956
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
