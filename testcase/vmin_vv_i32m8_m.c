/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1050135329, 1977900633, 1257890566, 3020688661, 1065903901, 2103527611, 2659201380, 1571693683, 1409543922, 2572508365, 2535384085, 73990452, 2439810983, 414422352, 824477346, 250629957
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1545060501, 602100684, 283719719, 2237856120, 545246275, 1772815741, 3665083064, 1520845535, 2194042254, 1042804469, 2981171142, 14357640, 798624424, 832153385, 2961595735, 2782791861
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    381614978, 2706707712, 1257149700, 1614627194, 1710871625, 139665544, 624367260, 1024146556, 3702013349, 399160854, 3335716951, 1033946140, 3757667955, 3681842317, 2299205841, 3134373773
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    381614978, 2706707712, 1257149700, 3020688661, 1065903901, 139665544, 624367260, 1024146556, 2194042254, 399160854, 3335716951, 73990452, 2439810983, 3681842317, 2961595735, 2782791861
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
