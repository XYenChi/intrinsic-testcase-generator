/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    175, 29, 122, 86, 160, 51, 7, 150, 86, 249, 77, 64, 28, 77, 93, 163
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    243, 7, 94, 188, 223, 129, 32, 111, 153, 187, 99, 124, 184, 234, 250, 141
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf8(size_t avl);
    const int out_data[] = {
    133, 29, 68, 93, 76, 73, 17, 36, 66, 236, 61, 135, 253, 94, 57, 32
    };
    const int8_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 0
    };
    const bool64_t *mask = &masked[0];
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8_m (mask, *in1, vl);
    vint8mf8_t data2_v = __riscv_vle8_v_i8mf8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i8mf8_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse8mf8_v_i8 (vbool8_t mask, int8mf8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    243, 29, 122, 188, 223, 73, 17, 150, 66, 236, 61, 124, 184, 234, 250, 32
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
