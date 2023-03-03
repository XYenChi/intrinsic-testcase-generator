/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    34726, 46275, 14709, 8213, 51320, 49780, 922, 17207, 635, 61507, 36529, 20659, 39944, 13664, 51198, 58326
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    64486, 10179, 10413, 37728, 39060, 16430, 51613, 37283, 3446, 1910, 42234, 58705, 52566, 61066, 2506, 48215
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4 (*in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4 (*in2, vl);
    vint16mf4_t out_v = __riscv_vle16_v_i16mf4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i16mf4 (data1_v, data2_v, vl);
        void vint16mf4_t __riscv_vse16_v_i16 (int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    99212, 56454, 25122, 45941, 90380, 66210, 52535, 54490, 4081, 63417, 78763, 79364, 92510, 74730, 53704, 106541
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
