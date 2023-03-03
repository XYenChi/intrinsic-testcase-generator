/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    45625, 1114, 1316, 22841, 38442, 46353, 3651, 23890, 60875, 7283, 24985, 22194, 4879, 17958, 63025, 20963
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    19869, 29994, 3247, 19317, 45526, 14673, 62599, 33772, 37936, 35709, 22611, 46496, 6142, 11859, 23048, 3922
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    44634, 63945, 30002, 35473, 54385, 20501, 51076, 49921, 14282, 17856, 37036, 11722, 23804, 5858, 26295, 59656
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    44634, 31108, 30002, 35473, 54385, 61026, 66250, 57662, 14282, 42992, 47596, 68690, 23804, 5858, 86073, 24885
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
