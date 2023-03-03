/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3783723720, 1158192643, 2595452469, 3413274204, 371104816, 2881491978, 2727087896, 3224540484, 2674904036, 2128548358, 3206577383, 3074119651, 2640367601, 3472468179, 253648268, 3740214092
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3341054834, 728880261, 4036736336, 2029126058, 2203855968, 670190462, 1509153000, 3383811508, 2310928382, 3457826993, 2257963777, 654426828, 3239815141, 2827334099, 3871878312, 2308406878
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    3379430626, 2008620970, 941068849, 402266222, 1973433962, 254409126, 2364825004, 1535437694, 1866062342, 2614942424, 3376139906, 3538334086, 3566456821, 2870449201, 1869537548, 4159661341
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3379430626, 728880261, 4036736336, 402266222, 1973433962, 670190462, 1509153000, 3383811508, 1866062342, 3457826993, 3376139906, 654426828, 3566456821, 2870449201, 1869537548, 4159661341
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
