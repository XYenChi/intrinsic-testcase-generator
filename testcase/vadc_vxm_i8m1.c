/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -77, -78, -60, -34, -119, 105, 113, 37, 34, -36, -115, 60, 88, -122, 49, 79
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -110, 79, 44, 92, 103, -20, 78, 49, 66, 34, -125, 127, -106, 98, 3, 61
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m1(avl);
    uint8_t masked[] = {
    0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1
    };
    const uint8_t *mask = &masked[0];
    vint8m1_t data1_v = __riscv_vle8_v_i8m1 (in1, vl);
    vint8m1_t data2_v = __riscv_vle8_v_i8m1 (in2, vl);
    vint8m1_t out_v = __riscv_vle8_v_i8m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vxm_i8m1 (data1_v, data2_v, masked, vl);
        void __riscv_vse8_v_i8m1 (int8_t *out, vint8m1_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -187, 2, -15, 59, -15, 85, 192, 87, 101, -1, -240, 188, -18, -23, 53, 141
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
