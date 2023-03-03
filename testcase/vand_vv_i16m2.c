/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    50008, 8287, 17974, 55618, 63263, 39989, 58351, 26572, 38910, 34414, 62210, 44349, 8861, 57603, 14238, 60281
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    28608, 57049, 59909, 54487, 41424, 42287, 23932, 60540, 53382, 57344, 46278, 15608, 41037, 18794, 39616, 57389
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2 (*in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2 (*in2, size_t vl);
    vint16m2_t out_v = __riscv_vle16_v_i16m2 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16m2_t __riscv_vse16_v_i16 (int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    28608, 57049, 59909, 54487, 41424, 42287, 23932, 60540, 53382, 57344, 46278, 15608, 41037, 18794, 39616, 57389
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
