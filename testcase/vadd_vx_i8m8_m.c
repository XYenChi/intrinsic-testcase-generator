/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    189, 204, 226, 163, 11, 33, 99, 143, 36, 129, 128, 189, 51, 116, 160, 62
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    234, 64, 98, 243, 187, 28, 148, 38, 206, 223, 226, 4, 92, 138, 98, 39
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m8(size_t avl);
    const int out_data[] = {
    232, 253, 107, 182, 80, 248, 8, 57, 92, 61, 79, 31, 60, 140, 82, 70
    };
    const int8_t *out = &out_data[0];
    bool1_t masked[] = {
    0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0
    };
    const bool1_t *mask = &masked[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8_m (mask, *in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i8m8_m (mask, data1_v, data2_v, vl);
        void vint1_t __riscv_vse8m8_v_i8 (vbool8_t mask, int8m8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    232, 253, 324, 406, 80, 248, 8, 57, 92, 352, 354, 31, 60, 140, 258, 70
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
