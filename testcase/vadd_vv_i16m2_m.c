/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    10647, 32968, 56694, 20804, 59509, 62812, 49472, 43710, 31966, 37123, 32896, 61324, 15304, 31429, 25416, 20575
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    21035, 42510, 50503, 50839, 28545, 46433, 5367, 56549, 57339, 46007, 51379, 20573, 18062, 52064, 26941, 43007
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    35943, 45033, 34487, 52148, 36784, 32248, 5, 26116, 44983, 7027, 6836, 40072, 23009, 3304, 27165, 18116
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    35943, 45033, 107197, 52148, 88054, 109245, 5, 26116, 44983, 7027, 84275, 81897, 33366, 83493, 27165, 63582
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
