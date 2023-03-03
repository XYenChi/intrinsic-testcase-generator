/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    61164, 23254, 28350, 21724, 60540, 18081, 44075, 2847, 7216, 48916, 11984, 52859, 51147, 60238, 42553, 46701
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    9212, 21646, 36190, 37838, 40645, 25463, 1744, 26213, 55981, 26339, 16028, 53347, 59850, 15639, 9150, 1000
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    12630, 6245, 17354, 25029, 45545, 30536, 34696, 56032, 54953, 34691, 38702, 59916, 21466, 3256, 37574, 65274
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vv_i16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    12630, 0, 17354, 25029, 0, 30536, 34696, 56032, 54953, 34691, 1, 1, 1, 0, 37574, 65274
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
