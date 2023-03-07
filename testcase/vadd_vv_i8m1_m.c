/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -112, 32, 30, -20, 105, -35, 84, -1, -80, 105, -122, -125, -88, -45, 52, -70
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    1, 34, 2, -20, -61, 121, -4, 100, 19, -90, -66, 73, -2, 9, 111, -121
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m1(avl);
    const int out_data[] = {
    73, -95, -94, -107, 69, -65, -71, 76, -42, 83, 102, -50, -98, -35, 43, 108
    };
    const int8_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint8m1_t data1_v = __riscv_vle8_v_i8m1_m (mask, *in1, vl);
    vint8m1_t data2_v = __riscv_vle8_v_i8m1_m (mask, *in2, vl);
    vint8m1_t data1_v = __riscv_vle8_v_i8m1_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i8m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m1 (bool8_t mask, int8_t *out, vint8m1_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    74, -94, -93, -106, 69, -64, -70, 77, -41, 83, 103, -49, -98, -34, 44, 109
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
