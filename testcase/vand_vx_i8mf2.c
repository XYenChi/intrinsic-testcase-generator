/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -87, 72, 80, -24, -93, -17, 34, -103, 108, 108, -79, 112, 80, 93, -114, -122
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -30, 84, -127, -60, -64, 3, 68, -44, 104, -17, -57, -4, -124, 94, -76, -52
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf2(avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2 (in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2 (in2, vl);
    vint8mf2_t out_v = __riscv_vle8_v_i8mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_i8mf2 (int8_t *out, vint8mf2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    226, 84, 129, 196, 192, 3, 68, 212, 104, 239, 199, 252, 132, 94, 180, 204
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
