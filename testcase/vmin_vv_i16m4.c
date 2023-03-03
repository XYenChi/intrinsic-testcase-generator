/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    35606, 8103, 65149, 23906, 17085, 53097, 43338, 33829, 59258, 48331, 33332, 55922, 7651, 57324, 62074, 796
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    29330, 64723, 10429, 15232, 40231, 15026, 10133, 30894, 34025, 31491, 64773, 42179, 10344, 47479, 21148, 44524
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
        out_v = __riscv_vmin_vv_i16m4 (data1_v, data2_v, vl);
        void vint16m4_t __riscv_vse16_v_i16 (int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    35606, 64723, 65149, 23906, 40231, 53097, 43338, 33829, 59258, 48331, 64773, 55922, 10344, 57324, 62074, 44524
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
