/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -42, -37, -128, 59, -71, -67, -65, 1, 31, -114, -98, 14, 26, 6, -68, 14
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    87, -83, -108, -36, -25, 123, 62, 10, 30, 126, 119, -99, 20, -48, 65, -41
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m8(avl);
    const int out_data[] = {
    1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1
    };
    const int8_t *out = &out_data[0];
    uint1_t masked[] = {
    0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0
    };
    const uint1_t *mask = &masked[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8 (in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8 (in2, vl);
    vint8m8_t out_v = __riscv_vle8_v_i8m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_i8m8 (int8_t *out, vint8m8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    1, 0, 20, 23, 1, 56, 0, 11, 1, 12, 21, 1, 1, 1, 253, 1
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
