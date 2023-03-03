/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3639664908, 1191698682, 2027059607, 1345754280, 2678169253, 135742952, 3459290610, 516776703, 1530338759, 745019908, 1462565660, 3617806269, 680101321, 1793297253, 1843795482, 1229841100
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3692165915, 1143634409, 529112791, 2967477441, 3273831534, 2673543205, 2261650067, 1657367535, 896135679, 2886360336, 4195782566, 1737062796, 2172209774, 1265839175, 3600930666, 1110089732
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    1422279597, 4013114254, 3571582702, 1600144936, 3701279374, 2591002326, 855505236, 183453728, 53113580, 187229765, 3368618779, 598689766, 3709112502, 2833899430, 3450241882, 182872619
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -52501008, 48064273, 1497946815, -1621723162, -595662282, -2537800254, 1197640543, -1140590833, 634203079, -2141340429, -2733216906, 1880743473, -1492108453, 527458078, -1757135184, 119751368
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
