/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    64216, 34113, 24405, 60882, 25542, 25747, 19315, 35491, 47004, 54360, 54542, 40306, 20927, 26670, 9861, 38478
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    33949, 33130, 43365, 61199, 49827, 52213, 52008, 44381, 41063, 49290, 19771, 30655, 37638, 32187, 39901, 3565
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    bool8_t masked[] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2 (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vx_i16m2 (data1_v, data2_v, size_t vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    64216, 34113, 24405, 60882, 25542, 25747, 19315, 35491, 47004, 49290, 54542, 40306, 20927, 32187, 39901, 3565
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
