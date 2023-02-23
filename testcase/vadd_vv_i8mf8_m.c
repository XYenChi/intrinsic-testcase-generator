/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    145, 245, 140, 106, 79, 179, 139, 45, 116, 55, 216, 3, 80, 217, 222, 140
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    236, 96, 249, 230, 90, 126, 2, 201, 196, 54, 50, 192, 196, 165, 185, 117
    };
    const int8_t *in2 = &data2[0];
    const int out_data[] = {
    192, 76, 80, 24, 53, 212, 117, 49, 73, 246, 226, 7, 178, 111, 237, 184
    };
    int8_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint8mf8_t out_data = __riscv_vadd_vv_i8mf8_m (mask, data1, data2, vl)
        vint8mf8_t __riscv_vse8_v_i8mf8 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    381, 76, 389, 24, 169, 212, 117, 246, 73, 109, 226, 7, 178, 382, 237, 184
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
