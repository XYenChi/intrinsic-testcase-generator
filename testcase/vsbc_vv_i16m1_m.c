/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    13426, 40282, 61280, 54321, 21713, 41061, 63975, 52460, 49681, 15024, 47049, 23057, 12075, 14583, 49356, 20530
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    10819, 37381, 7519, 17000, 5461, 58351, 316, 18471, 55220, 50489, 26403, 30792, 8143, 39655, 58126, 14787
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    31697, 9378, 42813, 23464, 21649, 41169, 51254, 10248, 8893, 85, 388, 60928, 54895, 11179, 3633, 11636
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    2606, 2900, 53761, 37321, 16251, -17290, 63658, 33989, -5540, -35466, 20645, -7735, 3931, -25072, -8770, 5743
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
