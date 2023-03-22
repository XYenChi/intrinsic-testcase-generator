/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -44, -76, 65, 112, 50, 80, -102, 102, -50, 82, 68, 28, -105, 75, -17, -13
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -120, 71, 19, -103, -62, 79, -37, 74, -55, 77, -4, -16, 18, 100, -54, -62
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    uint64_t masked[] = {
    0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1
    };
    const uint64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4 (in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4 (in2, vl);
    vint16mf4_t out_v = __riscv_vle16_v_i16mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vvm_i16mf4 (data1_v, data2_v, masked, vl);
        void __riscv_vse16_v_i16mf4 (int16_t *out, vint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -164, -5, 85, 10, -11, 159, -139, 177, -104, 159, 64, 12, -86, 175, -70, -74
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
