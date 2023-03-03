/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    5952, 27523, 4969, 39591, 62987, 41550, 12861, 19991, 45602, 19410, 30792, 16167, 32973, 6765, 28950, 44498
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    7980, 14151, 19775, 42686, 62539, 62531, 59244, 22463, 57454, 61513, 53670, 54618, 26356, 7778, 65346, 14965
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    12578, 52469, 31436, 36047, 56614, 17442, 47841, 1995, 64501, 11722, 28677, 26143, 61165, 19320, 16926, 49338
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    12578, 27523, 19775, 36047, 56614, 62531, 47841, 1995, 64501, 11722, 28677, 26143, 61165, 7778, 16926, 49338
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
