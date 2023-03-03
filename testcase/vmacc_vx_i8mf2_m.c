/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    204, 47, 52, 247, 224, 156, 199, 196, 208, 81, 231, 194, 110, 91, 69, 70
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    210, 156, 157, 249, 60, 71, 221, 52, 52, 24, 227, 86, 2, 138, 111, 167
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf2(size_t avl);
    const int out_data[] = {
    249, 100, 10, 182, 189, 120, 145, 55, 231, 28, 204, 188, 217, 225, 138, 64
    };
    const int8_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2_m (mask, *in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i8mf2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse8mf2_v_i8 (vbool8_t mask, int8mf2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    50797, 4701, 520, 44954, 42336, 18720, 28856, 10780, 48049, 2269, 47125, 36472, 23870, 20475, 9522, 4480
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
