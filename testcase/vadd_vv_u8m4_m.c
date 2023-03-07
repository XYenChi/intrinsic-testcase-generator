/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    124, -77, 20, 18, -63, 52, -39, -5, -22, 78, -71, -17, 32, -4, -12, -112
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -16, 21, 107, 104, 39, -3, 95, 14, -29, 70, 18, 27, -92, 47, -86, -58
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m4(avl);
    const int out_data[] = {
    -23, 12, 6, -107, 52, 73, 106, -45, -96, 78, -10, 120, -37, 123, -70, 111
    };
    const int8_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0
    };
    const bool2_t *mask = &masked[0];
    vint8m4_t data1_v = __riscv_vle8_v_i8m4_m (mask, *in1, vl);
    vint8m4_t data2_v = __riscv_vle8_v_i8m4_m (mask, *in2, vl);
    vint8m4_t data1_v = __riscv_vle8_v_i8m4_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u8m4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m4 (bool8_t mask, int8_t *out, vint8m4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -23, 13, 6, -106, 53, 73, 106, -45, -95, 78, -9, 120, -36, 123, -70, 111
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
