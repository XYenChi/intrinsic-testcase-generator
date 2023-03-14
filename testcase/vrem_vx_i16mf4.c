/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -53, 81, 72, -45, 25, 111, 37, 36, 123, -96, -35, 8, -99, -127, -4, -47
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -9, -61, -47, 91, 79, 40, 50, -118, -63, -26, 78, -52, -86, 117, 17, 66
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4 (in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4 (in2, vl);
    vint16mf4_t out_v = __riscv_vle16_v_i16mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i16mf4 (data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf4 (int16_t *out, vint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    65527, 20, 25, 65492, 4, 40, 13, 26, 60, 65510, 65509, 4, 65450, 65526, 65533, 65508
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
