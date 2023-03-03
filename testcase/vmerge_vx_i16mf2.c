/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    51343, 3752, 33710, 21174, 6069, 49430, 22364, 11296, 29044, 36563, 13325, 36883, 242, 54728, 30537, 60774
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    62387, 46952, 8174, 38358, 8709, 51582, 60009, 6015, 57430, 60383, 10396, 40481, 45352, 47467, 4945, 22166
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    bool32_t masked[] = {
    0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2 (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vx_i16mf2 (data1_v, data2_v, size_t vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    51343, 46952, 8174, 38358, 6069, 51582, 60009, 11296, 57430, 36563, 13325, 40481, 242, 47467, 4945, 60774
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
