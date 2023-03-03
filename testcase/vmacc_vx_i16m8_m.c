/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    26985, 34356, 25730, 36172, 36709, 6590, 17600, 40334, 47811, 46418, 29930, 668, 55698, 4199, 53834, 8864
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    11856, 4626, 11066, 19012, 61072, 5862, 11265, 15365, 13360, 15985, 31516, 47413, 29769, 26385, 28414, 49261
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    19070, 63985, 34154, 23606, 64107, 5315, 19785, 61502, 33575, 56949, 44487, 56406, 62882, 31863, 57992, 17352
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    514603950, 2198268661, 878782420, 853876233, 2353303864, 35025851, 348216001, 2480621668, 1605254325, 2643458683, 1331495910, 37679208, 3502401637, 133792738, 3121941328, 153808129
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
