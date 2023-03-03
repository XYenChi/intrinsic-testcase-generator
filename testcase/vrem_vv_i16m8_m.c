/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    51411, 44397, 41826, 21569, 33099, 13851, 17489, 1819, 28240, 636, 42792, 40092, 47135, 29061, 36119, 49474
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    43380, 55540, 16767, 39313, 4424, 57057, 42168, 24640, 19182, 45744, 3238, 237, 22736, 15325, 62829, 58059
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    7421, 50707, 31687, 46062, 34021, 10700, 32892, 7153, 16397, 57756, 55202, 56377, 1579, 15837, 17897, 54557
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    7421, 11143, 16767, 46062, 34021, 10700, 7190, 7153, 19182, 588, 55202, 56377, 22736, 15325, 26710, 54557
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
