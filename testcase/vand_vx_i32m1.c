/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    280621339, 744154599, 1337709359, 1328421875, 3109146893, 3944619457, 2028021224, 3917432488, 3974346125, 3928540064, 159669505, 895153744, 1573417265, 2946525138, 1201285761, 1631855531
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2202054930, 1853641021, 2337987435, 603205621, 4157918239, 2804014947, 713695991, 2627383049, 3585461789, 1321147297, 2796859411, 2684769719, 874025028, 4201588188, 505341514, 2302858616
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, size_t vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    2202054930, 1853641021, 2337987435, 603205621, 4157918239, 2804014947, 713695991, 2627383049, 3585461789, 1321147297, 2796859411, 2684769719, 874025028, 4201588188, 505341514, 2302858616
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
