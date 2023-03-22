/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -3, -77, 36, -5, -23, -58, 20, -34, -4, 87, -104, -32, -81, 23, -37, -81
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    27, -73, -2, 60, -60, 43, 73, 87, 65, -114, -80, -4, -67, 1, 121, 32
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m1(avl);
    const int out_data[] = {
    1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0
    };
    const int8_t *out = &out_data[0];
    uint8_t masked[] = {
    1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0
    };
    const uint8_t *mask = &masked[0];
    vint8m1_t data1_v = __riscv_vle8_v_i8m1_m (mask, in1, vl);
    vint8m1_t data2_v = __riscv_vle8_v_i8m1_m (mask, in2, vl);
    vint8m1_t out_v = __riscv_vle8_v_i8m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsub_vx_i8m1_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m1 (bool8_t mask, int8_t *out, vint8m1_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    226, 179, 1, 1, 1, 198, 203, 1, 187, 201, 0, 0, 0, 0, 0, 0
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
