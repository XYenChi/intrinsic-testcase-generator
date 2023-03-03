/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    198, 181, 233, 207, 145, 73, 233, 36, 112, 232, 18, 106, 243, 118, 42, 206
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    249, 1, 192, 113, 243, 119, 183, 41, 220, 122, 28, 105, 25, 254, 75, 116
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m8(size_t avl);
    const int out_data[] = {
    158, 24, 140, 63, 152, 254, 138, 223, 223, 67, 161, 151, 107, 153, 162, 161
    };
    const int8_t *out = &out_data[0];
    bool1_t masked[] = {
    1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1
    };
    const bool1_t *mask = &masked[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8_m (mask, *in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vx_i8m8_m (mask, data1_v, data2_v, vl);
        void vint1_t __riscv_vse8m8_v_i8 (vbool8_t mask, int8m8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -52, 180, 41, 93, -98, -47, 49, -6, -108, 110, -10, 0, 218, -136, -33, 89
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
