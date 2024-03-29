/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    10, -7, -57, -32, -48, 21, 28, -31, 94, -1, -15, -114, -92, 78, -32, 109
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    90, -66, 123, 10, -37, -90, -96, 124, 43, -6, -122, 83, -36, -41, 34, 86
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf2(avl);
    const int out_data[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0
    };
    const int8_t *out = &out_data[0];
    uint16_t masked[] = {
    0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0
    };
    const uint16_t *mask = &masked[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2 (in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2 (in2, vl);
    vint8mf2_t out_v = __riscv_vle8_v_i8mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_i8mf2 (int8_t *out, vint8mf2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    0, 1, 66, 234, 1, 187, 188, 93, 1, 0, 0, 1, 0, 1, 2, 0
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
