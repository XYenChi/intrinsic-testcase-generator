/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    36180, 28575, 22390, 65158, 39070, 9385, 50606, 47971, 6694, 38776, 746, 61751, 21184, 9500, 35152, 60893
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    24230, 58202, 26250, 33866, 44012, 41697, 59595, 51717, 2494, 37710, 11907, 35854, 7649, 21886, 28071, 5211
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    24162, 5255, 58410, 52549, 39145, 17374, 34717, 57996, 23015, 55546, 43697, 65169, 10502, 4595, 17741, 29384
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vx_i16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    11950, -29628, -3861, 31291, -4942, -32312, -8989, -3746, 4199, 1065, -11162, 25897, 13534, -12387, 7080, 55681
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
