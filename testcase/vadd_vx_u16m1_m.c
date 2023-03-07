/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -23806, -26620, 16130, 16315, -15507, -15094, -27233, -21953, -9794, 30116, -14234, 13770, -13143, 24276, 26615, 3389
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -14280, -7347, -11144, 31848, -5938, 9579, -27419, -7429, 18098, 23731, -24373, -26816, 19490, -10941, -24850, 10527
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m1(avl);
    const int out_data[] = {
    -3401, 27221, 12380, 5823, 17207, -6508, -10746, -477, 28546, -28948, 2166, 10475, -9607, 14526, -16820, -5838
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u16m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m1 (bool16_t mask, int16_t *out, vint16m1_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    -3401, 27221, 12380, 5824, 17207, -6508, -10746, -477, 28547, -28948, 2167, 10475, -9607, 14526, -16819, -5837
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
