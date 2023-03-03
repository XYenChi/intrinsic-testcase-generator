/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    72, 215, 148, 177, 208, 49, 216, 231, 175, 180, 202, 18, 138, 63, 211, 190
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    80, 3, 220, 209, 214, 162, 37, 76, 43, 53, 34, 49, 240, 77, 156, 148
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf8(size_t avl);
    const int out_data[] = {
    65, 61, 219, 155, 92, 0, 96, 224, 154, 158, 48, 199, 168, 240, 141, 42
    };
    const int8_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8_m (mask, *in1, vl);
    vint8mf8_t data2_v = __riscv_vle8_v_i8mf8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i8mf8_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse8mf8_v_i8 (vbool8_t mask, int8mf8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    80, 61, 220, 209, 92, 162, 216, 231, 154, 180, 202, 49, 168, 77, 141, 190
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
