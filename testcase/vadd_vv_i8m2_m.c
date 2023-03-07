/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    46, -91, 72, -111, -87, -35, 82, -40, -36, -99, 17, 15, 74, -108, -94, 37
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    67, -72, 39, -67, 3, 61, 15, 66, 51, -77, 0, -36, 25, 17, -20, 85
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m2(avl);
    const int out_data[] = {
    96, -57, -33, -33, -89, -77, 22, 63, -105, 44, 71, -71, 43, -126, 40, -61
    };
    const int8_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vint8m2_t data1_v = __riscv_vle8_v_i8m2_m (mask, *in1, vl);
    vint8m2_t data2_v = __riscv_vle8_v_i8m2_m (mask, *in2, vl);
    vint8m2_t data1_v = __riscv_vle8_v_i8m2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i8m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m2 (bool8_t mask, int8_t *out, vint8m2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    97, -57, -33, -32, -88, -77, 23, 64, -104, 44, 17, -71, 44, -125, 40, -60
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
