/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    75, 125, -84, -123, 51, -21, 17, 22, 72, -67, -73, 65, 122, -60, -118, 3
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    122, 19, 85, 79, -61, 92, -28, -97, 3, 80, -88, -77, -106, 28, -58, 123
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m8(avl);
    const int out_data[] = {
    86, -55, -48, 44, -126, 21, -59, -105, 107, -46, 69, -18, -114, -65, 112, -14
    };
    const int8_t *out = &out_data[0];
    bool1_t masked[] = {
    1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0
    };
    const bool1_t *mask = &masked[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8_m (mask, *in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8_m (mask, *in2, vl);
    vint8m8_t data1_v = __riscv_vle8_v_i8m8_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i8m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m8 (bool8_t mask, int8_t *out, vint8m8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    87, -54, -47, 44, -126, 22, -59, -105, 107, -45, 69, -17, -114, -64, 112, -14
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
