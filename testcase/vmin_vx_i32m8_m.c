/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1408580129, 3143242391, 3810231165, 3124513380, 2897595288, 2851064828, 3698826013, 3444921004, 3197838242, 4033075413, 71192560, 1327860127, 1509025028, 490704304, 324418488, 3102557928
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    96538124, 2125596637, 2336954354, 3869649027, 883470150, 4235712803, 838269831, 1855677162, 1745969527, 1586637930, 2239614287, 1832373859, 1669376549, 3975257094, 4070492498, 3801919652
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    3763813065, 3781170591, 366048986, 649894898, 3659824499, 1066282251, 3473021485, 2613812402, 3428090267, 1805827366, 2212469990, 1258160182, 2300986373, 3991285988, 3076916452, 3659471897
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3763813065, 3781170591, 3810231165, 649894898, 2897595288, 1066282251, 3698826013, 3444921004, 3197838242, 4033075413, 2212469990, 1258160182, 2300986373, 3991285988, 3076916452, 3659471897
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
