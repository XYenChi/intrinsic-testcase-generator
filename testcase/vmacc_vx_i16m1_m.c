/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    29673, 35981, 40036, 23890, 14753, 60119, 11655, 25993, 10030, 44186, 62108, 42908, 13435, 47557, 12424, 18457
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    59380, 47889, 19750, 29154, 16097, 12040, 56424, 59682, 63746, 7277, 16029, 51170, 51779, 62602, 47421, 45229
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    13280, 215, 14992, 64953, 64058, 38048, 60478, 47743, 64748, 3912, 34714, 8657, 53079, 56550, 51110, 21608
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    394057440, 7735916, 600219712, 1551727171, 945047675, 2287407713, 704871091, 1240983799, 649422440, 172855633, 2156017113, 371454556, 713116365, 2689348350, 634990641, 398818856
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
