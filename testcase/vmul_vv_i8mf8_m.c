/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -90, -92, -121, -7, 20, -43, 108, 55, 10, 33, -36, 100, 119, 18, -105, 26
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    26, -37, 112, 21, -114, -21, 103, -55, -45, 37, 59, -79, 11, -104, 83, -29
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf8(avl);
    const int out_data[] = {
    0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1
    };
    const int8_t *out = &out_data[0];
    uint64_t masked[] = {
    0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0
    };
    const uint64_t *mask = &masked[0];
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8_m (mask, in1, vl);
    vint8mf8_t data2_v = __riscv_vle8_v_i8mf8_m (mask, in2, vl);
    vint8mf8_t out_v = __riscv_vle8_v_i8mf8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i8mf8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf8 (bool8_t mask, int8_t *out, vint8mf8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    0, 0, 0, 1, 1, 135, 0, 47, 62, 0, 0, 36, 29, 176, 1, 1
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
