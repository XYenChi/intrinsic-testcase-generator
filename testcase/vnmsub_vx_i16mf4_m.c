/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    46, -18, 55, 43, -34, 90, -21, 36, -85, -36, -12, 62, -103, -74, -20, -52
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -46, -55, 97, 81, -42, -104, -18, 94, -42, -86, 112, -115, 33, 121, -62, 4
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    const int out_data[] = {
    1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0
    };
    const int16_t *out = &out_data[0];
    uint64_t masked[] = {
    0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1
    };
    const uint64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, in2, vl);
    vint16mf4_t out_v = __riscv_vle16_v_i16mf4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsub_vx_i16mf4_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf4 (bool16_t mask, int16_t *out, vint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    1, 37, 65494, 1, 8, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 65484
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
