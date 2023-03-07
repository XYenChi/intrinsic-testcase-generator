/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    18352, 4097, 27935, -17837, 15413, 4974, -14679, 22691, 21189, 10016, -5337, 1871, 27821, 8096, 14475, -22966
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -27728, 15032, 3789, 30320, -6916, -17468, -23683, 10709, 22140, -20108, 21866, -22702, 29952, 31823, 28675, 14686
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    const int out_data[] = {
    -4210, -27635, -24083, -30826, 30322, -26897, -28657, 30111, 7582, 10818, -620, -942, -20473, 26212, -8839, 5817
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i16m4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m4 (bool16_t mask, int16_t *out, vint16m4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -4209, -27635, -24083, -30825, 30322, -26897, -28657, 30111, 7582, 10818, -620, -941, -20472, 26212, -8839, 5817
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
