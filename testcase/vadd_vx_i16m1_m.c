/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    27279, -24976, -14745, 15298, -26513, 2540, -2703, 10982, 10333, -20200, -26934, -3207, 3912, -7901, -12814, -4152
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -20600, -2040, 22833, -30276, -27834, -27873, -6072, 23894, 16465, -9530, -8386, -21389, -6841, 24510, -104, -16831
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m1(avl);
    const int out_data[] = {
    -18856, -7102, 14565, -1376, 12152, 4494, -14851, -20040, 27113, 17681, 27894, 9368, 16487, -21346, -32194, -7395
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i16m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m1 (bool16_t mask, int16_t *out, vint16m1_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -18855, -7102, 14565, -1376, 12153, 4494, -14850, -20039, 27114, 17682, 27895, 9369, 16487, -21345, -32194, -7394
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
