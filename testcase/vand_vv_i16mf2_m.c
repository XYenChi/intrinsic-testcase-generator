/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    24345, 16148, 8807, 49481, 48755, 63807, 24320, 17619, 44080, 26425, 28748, 1639, 20353, 45088, 32995, 62951
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    47413, 50589, 32469, 53609, 57994, 11310, 43509, 8106, 45935, 3873, 46580, 57481, 1547, 43314, 15534, 25574
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    36176, 58257, 27171, 46709, 2147, 27776, 40349, 30651, 37307, 65332, 36381, 3331, 57868, 43948, 17366, 4969
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    36176, 50589, 27171, 53609, 57994, 11310, 43509, 8106, 37307, 65332, 36381, 3331, 57868, 43314, 17366, 4969
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
