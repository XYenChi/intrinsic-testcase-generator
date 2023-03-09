/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1357986050, 1368322562, 1109735221, -914056849, 1039107506, 1623119598, -1219266704, 1491332965, -1345026050, 2131707882, -474495417, -279844403, 1314848581, 1514584875, 1306679582, -1725197276
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    576958993, -996248108, -845337363, -423983405, -1383055498, -2123693785, 800502911, -1272650252, -914983131, 890227430, 1015298500, 1220725044, -2009797210, 457686474, -249642942, -1678850407
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    bool32_t masked[] = {
    1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m1 (int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1934945044, 372074455, 264397859, -1338040254, -343947992, -500574186, -418763792, 218682713, -2260009180, 3021935313, 540803083, 940880641, -694948628, 1972271349, 1057036641, -3404047683
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
