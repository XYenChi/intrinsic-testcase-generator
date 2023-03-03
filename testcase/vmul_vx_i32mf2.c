/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    661017711, 2703467769, 1504907872, 1401389432, 548593638, 3349249232, 305534410, 3688303889, 2726613163, 3561266482, 1827190566, 2914708200, 881990852, 960978585, 1644489361, 3176193162
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    4201165734, 1770527398, 1737052202, 3593987509, 1741145322, 3084320115, 4271401376, 2704454833, 1846082810, 1960768228, 3013718009, 3627430234, 2807588092, 1445743214, 1929410135, 1887781565
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i32mf2 (data1_v, data2_v, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    2777044957020314874, 4786563754624435062, 2614103532864734144, 5036576113852604888, 955181246482661436, 10330156776405901680, 1305060099289348160, 9974851278178745537, 5033553689734028030, 6982818169346933896, 5506637114629103094, 10572900647967718800, 2476267013328134384, 1389328268063072190, 3172894440013073735, 5995958898102658530
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
