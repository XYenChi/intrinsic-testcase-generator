/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    357232538, 132828445, 4114455155, 3168991872, 1696285310, 3978293378, 1708669200, 3062082490, 2176839358, 1644179198, 1333724599, 3441537177, 2781863572, 512921986, 2907199915, 1067579330
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3976870072, 2934952175, 1158159392, 1200763438, 3116514275, 202403935, 2168843929, 1033550146, 991168198, 1905723119, 1932282009, 2529771621, 2598512671, 4069508870, 3342322851, 3202841950
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vx_i32m4 (data1_v, data2_v, mask, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    4334102610, 3067780620, 5272614547, 4369755310, 4812799585, 4180697313, 3877513129, 4095632636, 3168007556, 3549902317, 3266006608, 5971308798, 5380376243, 4582430856, 6249522766, 4270421280
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
