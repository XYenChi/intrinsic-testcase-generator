/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    104, -74, 25, 26, 36, -58, -3, 26, 14, -58, 39, -10, 45, -96, -24, -31
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -22, 96, -74, -33, 91, 12, -112, -2, 50, 7, 118, -76, -68, 118, -3, -17
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int out_data[] = {
    1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0
    };
    const int32_t *out = &out_data[0];
    uint4_t masked[] = {
    0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0
    };
    const uint4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i32m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m8 (bool32_t mask, int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1, 96, 25, 0, 0, 12, 4294967293, 1, 1, 1, 1, 1, 45, 118, 4294967293, 0
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
