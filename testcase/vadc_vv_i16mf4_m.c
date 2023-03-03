/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    37319, 20059, 46082, 58742, 42953, 30441, 42278, 23911, 5627, 24012, 54548, 10153, 37830, 63, 63811, 14479
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    46204, 1246, 19234, 765, 53619, 23994, 18748, 62466, 42487, 20346, 31743, 43163, 35393, 15504, 57229, 19006
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    37116, 40803, 5920, 51176, 5422, 20758, 20699, 10204, 14175, 33866, 65307, 6263, 35532, 25140, 3473, 34996
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    83523, 21305, 65316, 59507, 96573, 54436, 61026, 86377, 48115, 44359, 86292, 53317, 73224, 15567, 121041, 33486
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
