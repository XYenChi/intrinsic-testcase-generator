/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    16797, 51155, 24824, 37247, 53964, 59452, 26494, 62540, 15956, 1613, 58276, 60889, 24860, 26287, 37895, 10453
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    59660, 45573, 52671, 15634, 26295, 42072, 54631, 22618, 56070, 3748, 61984, 38922, 35989, 27175, 929, 32979
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    24997, 39831, 44514, 8001, 11195, 53767, 65204, 29315, 11530, 54175, 7199, 65016, 7158, 7560, 4461, 46100
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    24997, 39831, 52671, 8001, 53964, 53767, 65204, 29315, 11530, 3748, 61984, 60889, 7158, 27175, 37895, 46100
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
