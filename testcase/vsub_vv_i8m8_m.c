/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    71, 67, 15, 65, -51, 52, -117, -104, 41, 97, 40, -127, 13, 74, -41, 35
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -52, 64, -105, -101, -88, -9, -10, -44, -98, -81, 62, -65, 31, -6, -123, 40
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m8(avl);
    const int out_data[] = {
    1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1
    };
    const int8_t *out = &out_data[0];
    uint1_t masked[] = {
    0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0
    };
    const uint1_t *mask = &masked[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8_m (mask, in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8_m (mask, in2, vl);
    vint8m8_t out_v = __riscv_vle8_v_i8m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_i8m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m8 (bool8_t mask, int8_t *out, vint8m8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    1, 3, 120, 166, 1, 61, 149, 196, 139, 0, 0, 0, 1, 0, 82, 1
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
