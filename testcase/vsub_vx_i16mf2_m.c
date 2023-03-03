/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    55074, 7356, 36454, 14846, 52954, 60171, 4377, 47930, 46559, 18993, 56582, 11799, 11969, 62275, 162, 14188
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    36467, 18684, 1147, 55926, 64306, 26889, 61813, 30301, 3077, 14051, 51504, 51571, 9629, 22661, 30578, 41097
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    57104, 543, 37130, 40933, 26652, 17035, 6744, 37105, 20025, 56408, 29255, 12191, 64526, 459, 60163, 30318
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    18607, 543, 37130, 40933, -11352, 17035, -57436, 37105, 43482, 4942, 5078, -39772, 2340, 459, -30416, -26909
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
