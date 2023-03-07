/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -27491, -757, -9817, -3255, 16864, -25543, -10608, 30144, 10048, 32460, 19730, 25320, -18244, -16506, -16802, 16867
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -30642, 14672, 6485, 10970, -18002, 169, -28912, -7315, 15468, 1665, 13485, 6556, 4241, -13430, -13509, -28359
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2 (*in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2 (*in2, vl);
    vint16mf2_t out_v = __riscv_vle16_v_i16mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u16mf2 (data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf2 (int16_t *out, vint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    -33807, -32570, -6771, -1634, -7445, -31025, -12233, 6585, 14108, 6310, 322, 46806, -39359, 9900, -9170, 14621
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
