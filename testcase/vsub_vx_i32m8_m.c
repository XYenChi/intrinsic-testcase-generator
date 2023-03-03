/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3809256118, 2960780411, 1852651100, 2697608720, 2006043794, 4202983611, 1166317223, 756845250, 4275180675, 2141277016, 735161479, 4243260509, 1232241626, 189975264, 3987664262, 1458520882
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2981137386, 1608239979, 1283124968, 2957485387, 1214295319, 3094329528, 3484766481, 1026078724, 1387805834, 3343495821, 3351974379, 2835495295, 482026267, 1709847109, 3751993646, 497721591
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    352057081, 2584495300, 2225916384, 1878092489, 1474036620, 1168049348, 3781466665, 2182737873, 4109667180, 1807181694, 1879949392, 628710455, 2458867864, 270651673, 2313160709, 1138200840
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    352057081, 1352540432, 2225916384, -259876667, 791748475, 1168049348, 3781466665, 2182737873, 2887374841, -1202218805, -2616812900, 1407765214, 750215359, 270651673, 2313160709, 960799291
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
