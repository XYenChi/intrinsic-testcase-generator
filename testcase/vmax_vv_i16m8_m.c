/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    55350, 44011, 27592, 16182, 53442, 40389, 59033, 54765, 10900, 35666, 41867, 20602, 16725, 49735, 25682, 6172
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    41357, 32146, 8508, 47141, 5515, 45238, 57469, 49514, 65079, 47707, 21170, 4525, 35138, 1038, 59615, 53234
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    46810, 5182, 24986, 48464, 34111, 29848, 61654, 71, 8992, 3711, 24862, 63690, 55698, 46374, 17937, 43763
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    55350, 5182, 24986, 48464, 34111, 45238, 59033, 71, 8992, 3711, 41867, 63690, 55698, 46374, 17937, 43763
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
