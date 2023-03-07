/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    22, 84, 59, -65, -17, 97, 111, 58, 114, 76, -116, -45, 23, -25, -87, 119
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -40, 0, 36, -29, -58, 116, -4, 119, 52, 94, -80, 107, 74, 14, -122, -112
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf8(avl);
    const int out_data[] = {
    49, -50, -79, -29, 116, -107, -5, 57, 24, -17, -32, 58, -70, 48, 100, 6
    };
    const int8_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1
    };
    const bool64_t *mask = &masked[0];
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8_m (mask, *in1, vl);
    vint8mf8_t data2_v = __riscv_vle8_v_i8mf8_m (mask, *in2, vl);
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i8mf8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf8 (bool8_t mask, int8_t *out, vint8mf8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    49, 84, -79, -28, 117, -107, -4, 57, 25, -17, -31, 58, -69, 49, 101, 7
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
