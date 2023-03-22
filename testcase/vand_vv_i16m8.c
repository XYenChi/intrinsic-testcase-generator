/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    24, -100, 88, -96, 59, 79, 87, -8, -40, 9, 80, -70, -9, -101, 97, -74
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    102, -68, -41, 52, -54, -112, -41, -11, 105, 81, -28, 117, 86, 71, -39, 29
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8 (in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8 (in2, vl);
    vint16m8_t out_v = __riscv_vle16_v_i16m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_i16m8 (int16_t *out, vint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    102, 65468, 65495, 52, 65482, 65424, 65495, 65525, 105, 81, 65508, 117, 86, 71, 65497, 29
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
