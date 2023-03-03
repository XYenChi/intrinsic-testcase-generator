/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    58605, 47341, 46705, 19225, 54315, 55846, 25013, 50793, 64393, 19387, 53694, 36952, 29526, 46829, 12004, 47828
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    33551, 7744, 64759, 62333, 30607, 54558, 47256, 57006, 6317, 21189, 18766, 55319, 59757, 5070, 21442, 21349
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    28720, 11570, 51281, 63154, 42112, 49008, 16950, 42411, 9314, 61551, 24929, 3963, 11432, 35869, 25815, 31947
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    58605, 11570, 51281, 62333, 42112, 55846, 16950, 57006, 64393, 61551, 24929, 3963, 11432, 35869, 25815, 31947
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
