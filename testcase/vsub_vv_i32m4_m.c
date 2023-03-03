/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2044006319, 2508643421, 1995574071, 3806868381, 1181351680, 2586518082, 3742286096, 3697192053, 2184617956, 3716296982, 3589009943, 4260072865, 3263817344, 2906497371, 2127181283, 1962573817
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1770400493, 2298105103, 3907878636, 1860451735, 2890986481, 3824743015, 4082698156, 2874834943, 1331592057, 34165580, 3917274836, 2212634533, 4142201636, 4215156566, 4243395911, 3691873179
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    2905455424, 95175209, 652064101, 3359201529, 1236806561, 4262783649, 4239491195, 4240657169, 3467154608, 101992204, 3888431984, 1877168465, 684044700, 3461857921, 2933887198, 1475568813
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    2905455424, 95175209, 652064101, 3359201529, -1709634801, -1238224933, -340412060, 822357110, 853025899, 101992204, -328264893, 1877168465, 684044700, -1308659195, 2933887198, -1729299362
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
