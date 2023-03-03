/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4036163757, 102493984, 2937345208, 2742425180, 2864088555, 1961118920, 2929778684, 1446240887, 3495654714, 1324254450, 1214882593, 3355598135, 874838084, 4123326917, 2120475429, 2540848433
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2903895297, 2697480178, 311308423, 2291702784, 1257853633, 1161965069, 3376018564, 3852112883, 3732918923, 1846027637, 1931061454, 1480499025, 2196152619, 2977423268, 1708872736, 1851797236
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vx_i32mf2 (data1_v, data2_v, mask, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    6940059054, 2799974162, 3248653631, 5034127964, 4121942188, 3123083989, 6305797248, 5298353770, 7228573637, 3170282087, 3145944047, 4836097160, 3070990703, 7100750185, 3829348165, 4392645669
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
