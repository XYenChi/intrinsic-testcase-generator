/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -3, -79, -36, 23, 39, 102, 21, 0, 58, 23, -35, -110, -7, 22, -64, -76
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -122, 43, 44, 26, -19, 0, -128, 64, -9, -20, -17, 0, 74, 65, 110, -121
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf8(avl);
    const int out_data[] = {
    19, -59, 2, -91, 46, 47, -60, -80, 60, -58, 125, -71, 25, -75, -52, -117
    };
    const int8_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8_m (mask, *in1, vl);
    vint8mf8_t data2_v = __riscv_vle8_v_i8mf8_m (mask, *in2, vl);
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i8mf8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf8 (bool8_t mask, int8_t *out, vint8mf8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    20, -58, 2, -91, 47, 102, -59, -79, 60, -58, 126, -110, 26, -75, -52, -117
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
