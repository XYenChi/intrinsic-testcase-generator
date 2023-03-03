/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    181, 219, 220, 201, 123, 71, 170, 130, 237, 70, 6, 148, 227, 197, 184, 6
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    204, 105, 188, 70, 144, 177, 239, 38, 40, 238, 13, 7, 191, 150, 103, 85
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf8(size_t avl);
    const int out_data[] = {
    72, 164, 200, 139, 195, 197, 61, 0, 71, 141, 17, 225, 230, 215, 78, 199
    };
    const int8_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0
    };
    const bool64_t *mask = &masked[0];
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8_m (mask, *in1, vl);
    vint8mf8_t data2_v = __riscv_vle8_v_i8mf8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint64_t __riscv_vse8mf8_v_i8 (vbool8_t mask, int8mf8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    385, 324, 408, 271, 268, 249, 409, 169, 278, 308, 19, 155, 418, 348, 288, 91
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
