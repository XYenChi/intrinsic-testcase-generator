/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1062468565, 3910186836, 1650754375, 1474712334, 1812340170, 157026312, 3797803825, 2276074368, 2843682103, 851612882, 590373080, 1961084074, 2186776974, 2864845201, 1300547821, 2230930592
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    382702341, 2724220775, 3206916908, 3312743678, 1388165171, 1217889354, 2456750776, 1446897229, 1617341349, 913404567, 902137949, 529658507, 2188135519, 2175519731, 1597917154, 3227504219
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vx_i32m2 (data1_v, data2_v, mask, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1445170906, 6634407611, 4857671283, 4787456012, 3200505341, 1374915666, 6254554601, 3722971597, 4461023452, 1765017449, 1492511029, 2490742581, 4374912493, 5040364932, 2898464975, 5458434811
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
