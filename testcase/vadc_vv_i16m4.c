/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    18498, 5606, 25041, 47175, 43695, 17337, 19999, 55170, 44062, 65258, 28664, 21877, 27905, 23265, 59525, 47555
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    35656, 40264, 26099, 419, 38107, 37719, 56257, 12080, 19987, 63549, 4028, 37687, 30718, 27454, 9347, 42501
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
        out_v = __riscv_vadc_vv_i16m4 (data1_v, data2_v, mask, vl);
        void vint16m4_t __riscv_vse16_v_i16 (int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    54154, 45870, 51140, 47594, 81802, 55056, 76256, 67250, 64049, 128807, 32692, 59564, 58623, 50719, 68872, 90056
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
