/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    37614, 4606, 16690, 13525, 46281, 65012, 14661, 11328, 15039, 9887, 56709, 59405, 22912, 24303, 58826, 55307
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    17606, 53178, 45088, 17229, 46343, 9051, 50351, 46191, 44389, 43961, 5593, 32152, 55991, 17188, 36388, 18353
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    54319, 33336, 30439, 31507, 20279, 26161, 44408, 25630, 61641, 5530, 30055, 1249, 16080, 45577, 8950, 14067
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vv_i16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    0, 33336, 30439, 1, 20279, 26161, 3, 25630, 2, 5530, 0, 0, 2, 45577, 8950, 14067
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
