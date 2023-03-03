/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2040473311, 1484233395, 753051905, 4165977312, 859098187, 868819343, 2819320664, 3703220368, 3159055585, 2703177242, 3799342306, 767183722, 116231753, 1515598608, 3264664288, 2450146837
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1893800697, 2883570047, 2421078611, 3094734883, 1164324749, 2901784533, 4245016190, 1090285592, 2431238796, 589174276, 3505868855, 2710014436, 2549482629, 397173184, 2579408729, 3520264400
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    1800197135, 2744823375, 2024043187, 2639900238, 1515000551, 209072301, 3414755635, 2678802262, 3031997447, 2874849872, 2600356263, 4015580352, 536686374, 2640587209, 466881497, 2665454025
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3864249778581697767, 4279890960579119565, 1823197860168303955, 2639900238, 1515000551, 2521126531488621819, 3414755635, 4037567811231337856, 7680418496972475660, 2874849872, 13319995860089279630, 4015580352, 296330835211718637, 601955124805327872, 466881497, 2665454025
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
