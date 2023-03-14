/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -53, 108, 98, -41, -38, 120, -128, 90, -66, 71, 119, 124, 55, -13, -39, -32
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -70, 43, 42, -102, -113, 75, -101, 17, 11, 55, -33, 69, 126, -102, 87, -77
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf4(avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4 (in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4 (in2, vl);
    vint8mf4_t out_v = __riscv_vle8_v_i8mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vv_i8mf4 (out_data, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf4 (int8_t *out, vint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    130, 221, 236, 170, 59, 216, 129, 7, 215, 192, 88, 148, 238, 210, 66, 96
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
