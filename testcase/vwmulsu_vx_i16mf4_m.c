/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -96, 50, 86, 27, 34, 101, 27, -117, -32, 40, 56, -51, 117, 2, 87, 55
    };
    const int16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    -30, -82, -117, 40, 87, -64, -8, -26, -67, -82, -2, 57, -114, 41, 16, -106
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    const int out_data[] = {
    1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };
    const int16_t *out = &out_data[0];
    uint64_t masked[] = {
    1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1
    };
    const uint64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, in1, vl);
    vuint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, in2, vl);
    vint16mf4_t out_v = __riscv_vle16_v_i16mf4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vwmulsu_vx_i16mf4_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf4 (bool16_t mask, int16_t *out, vint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    2880, 0, 1, 0, 1, 1, 0, 3042, 1, 1, 1, 62629, 52198, 82, 1392, 59706
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