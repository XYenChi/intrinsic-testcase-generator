/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    32438, 26443, 21905, 55874, 47019, 39747, 13161, 47355, 44636, 49606, 34577, 41682, 29366, 7021, 62283, 49128
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    61014, 46703, 8402, 56283, 28985, 44756, 37486, 29742, 29102, 2957, 13428, 65101, 43181, 53129, 8722, 33076
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    50293, 45126, 54451, 57717, 60557, 59898, 63707, 61770, 29916, 56009, 57896, 15392, 52580, 64129, 17051, 57652
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    28576, 20260, 54451, 409, 28985, 5009, 11164, 61770, 29102, 2957, 57896, 15392, 52580, 64129, 8722, 57652
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
