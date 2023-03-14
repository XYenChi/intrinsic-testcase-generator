/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -97, -96, -93, -101, -56, 115, 23, -50, 42, -53, 45, -28, -49, 67, -98, -8
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    27, -11, 16, -9, -94, -82, -88, 42, 80, -76, -70, 43, 70, -89, -98, 67
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf4(avl);
    const int out_data[] = {
    1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0
    };
    const int8_t *out = &out_data[0];
    uint32_t masked[] = {
    0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1
    };
    const uint32_t *mask = &masked[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4_m (mask, in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4_m (mask, in2, vl);
    vint8mf4_t out_v = __riscv_vle8_v_i8mf4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vor_wx_8mf4i_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8mf4 (bool8_t mask, int8_t *out, vint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    1, 245, 0, 255, 0, 1, 1, 1, 122, 0, 1, 239, 0, 1, 158, 251
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
