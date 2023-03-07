/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -21, 37, 10, 119, -113, -38, -112, 11, -12, 54, -77, 122, -6, 110, -99, -62
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    71, -114, 83, 54, -45, -91, 121, 117, 118, 8, 99, 15, 50, -90, 18, -105
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m8(avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8 (*in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8 (*in2, vl);
    vint8m8_t out_v = __riscv_vle8_v_i8m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i8m8 (data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m8 (int8_t *out, vint8m8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    -1, 127, -80, 88, -206, -59, -151, 128, 33, 176, -186, 128, 98, 42, -92, -34
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
