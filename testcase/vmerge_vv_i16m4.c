/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    14148, 44287, 9959, 64049, 56089, 15444, 38744, 74, 25066, 3157, 4977, 15348, 29009, 33532, 18607, 14741
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    22228, 15067, 12433, 64049, 11760, 61529, 10749, 6506, 42578, 26303, 21305, 44800, 9158, 12460, 56327, 26328
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    bool4_t masked[] = {
    0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4 (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vv_i16m4 (data1_v, data2_v, size_t vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    14148, 15067, 9959, 64049, 56089, 15444, 10749, 6506, 25066, 26303, 4977, 15348, 29009, 12460, 18607, 14741
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
