/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    48985, 12208, 50058, 58862, 62354, 52147, 7340, 24643, 25207, 10874, 5451, 40527, 15924, 5087, 1169, 36513
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    19136, 19813, 62900, 10523, 12513, 41951, 33210, 60685, 30142, 7053, 39470, 15157, 32227, 51415, 56667, 34656
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    58163, 21477, 53765, 45769, 8841, 2757, 20765, 17305, 19923, 23966, 15559, 32322, 6528, 19268, 33060, 5210
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vv_i16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    58163, 1, 53765, 0, 8841, 0, 20765, 17305, 19923, 0, 7, 32322, 6528, 10, 33060, 0
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
