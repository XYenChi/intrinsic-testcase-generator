/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    42969, 47437, 63856, 48037, 17352, 36921, 10444, 30290, 10806, 2774, 48607, 15355, 61154, 57397, 55523, 60411
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    42160, 19133, 21111, 20773, 2240, 18597, 19036, 9730, 34032, 61956, 11554, 22140, 14364, 50573, 14596, 64172
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    47517, 37781, 51503, 36620, 1145, 46718, 37885, 23039, 14241, 62311, 23958, 15599, 45844, 37230, 11371, 42786
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    85129, 66571, 84968, 68810, 19593, 55519, 29481, 40021, 44839, 64730, 60162, 37496, 75519, 107970, 70120, 124583
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
