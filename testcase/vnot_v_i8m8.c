/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -30, 90, 44, -69, 46, -59, 100, -9, -103, 15, -53, -78, -38, -123, 126, 116
    };
    const int8_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m8(avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8 (in1, vl);
    vint8m8_t out_v = __riscv_vle8_v_i8m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnot_v_i8m8 (data1_v, vl);
        void __riscv_vse8_v_i8m8 (int8_t *out, vint8m8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    29, -91, -45, 68, -47, 58, -101, 8, 102, -16, 52, 77, 37, 122, -127, -117
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
