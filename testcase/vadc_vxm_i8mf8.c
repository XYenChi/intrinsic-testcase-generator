/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -71, -69, -23, 49, 62, -69, -90, -12, 15, -49, -84, 122, -71, 53, 30, -2
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    37, -11, 15, -74, 2, -54, -101, -125, 94, -23, 25, 95, 38, -7, -93, 25
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf8(avl);
    uint64_t masked[] = {
    0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0
    };
    const uint64_t *mask = &masked[0];
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8 (in1, vl);
    vint8mf8_t data2_v = __riscv_vle8_v_i8mf8 (in2, vl);
    vint8mf8_t out_v = __riscv_vle8_v_i8mf8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vxm_i8mf8 (data1_v, data2_v, masked, vl);
        void __riscv_vse8_v_i8mf8 (int8_t *out, vint8mf8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -34, -79, -7, -25, 65, -122, -190, -136, 109, -71, -58, 218, -32, 46, -62, 23
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
