/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -5, 104, 106, 46, -59, 77, 26, -70, 94, -72, -126, 50, 99, 68, 79, 47
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -65, 54, 27, -42, 9, 49, -2, 40, 50, -121, 104, -26, 63, -71, -100, -110
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    uint8_t masked[] = {
    1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1
    };
    const uint8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2 (in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2 (in2, vl);
    vint16m2_t out_v = __riscv_vle16_v_i16m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vvm_i16m2 (data1_v, data2_v, masked size_t vl);
        void __riscv_vse16_v_i16m2 (int16_t *out, vint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -65, 104, 27, -42, -59, 49, -2, -70, 50, -72, 104, -26, 99, 68, 79, -110
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
