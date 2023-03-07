/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    879700742, 295952452, -25456871, 190521507, -16670474, -301323533, -762590424, 322854413, -495237625, -1490714274, -1285437700, -803949630, -784252482, -1663527048, -1086377819, 1233676494
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -1660449496, -1103359040, -2075851123, 412785983, -1405698703, -1426830036, -1712204190, -927357925, -2056269051, 95939913, 475382813, -1962952384, -1993582401, -2008181237, -2063786559, -400145050
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u32mf2 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32mf2 (int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    -141180512, 2369394805, -507975921, -1859807855, -2129193227, -67118767, -2150502032, -1472310497, 1044655804, -1621873444, -2340086011, -2573909210, -217631683, -3334532208, 195863249, 59899182
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
