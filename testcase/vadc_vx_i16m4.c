/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    9534, 31678, 10223, 42794, 14149, 14051, 1469, 786, 51559, 58283, 36067, 36930, 25959, 24893, 22238, 450
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    61847, 13822, 46451, 12183, 47141, 30201, 38866, 39937, 27562, 50037, 61236, 64665, 59258, 14521, 26915, 6078
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
        out_v = __riscv_vadc_vx_i16m4 (data1_v, data2_v, mask, vl);
        void vint16m4_t __riscv_vse16_v_i16 (int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    71381, 45500, 56674, 54977, 61290, 44252, 40335, 40723, 79121, 108320, 97303, 101595, 85217, 39414, 49153, 6528
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
