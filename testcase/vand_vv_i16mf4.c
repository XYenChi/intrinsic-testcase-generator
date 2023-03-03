/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    54841, 31872, 47831, 42757, 20683, 62036, 26457, 31564, 11641, 21202, 29925, 64511, 40410, 64671, 38039, 1555
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    35194, 45628, 59634, 18664, 50938, 65130, 60120, 2309, 57010, 4026, 55005, 49328, 50464, 20653, 25115, 58466
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4 (*in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4 (*in2, size_t vl);
    vint16mf4_t out_v = __riscv_vle16_v_i16mf4 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16mf4_t __riscv_vse16_v_i16 (int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    35194, 45628, 59634, 18664, 50938, 65130, 60120, 2309, 57010, 4026, 55005, 49328, 50464, 20653, 25115, 58466
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
