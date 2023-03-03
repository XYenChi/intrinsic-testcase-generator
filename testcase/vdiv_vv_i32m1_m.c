/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3572962402, 3532962924, 2188882605, 261789886, 2063171106, 2979870758, 375931732, 341964309, 1164958092, 2696015411, 2165780617, 2113269774, 1778099022, 2535455668, 3840984966, 2763392493
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3902541846, 2341359482, 2714369219, 2435087733, 3222337796, 2990310998, 1314626301, 3351346879, 2502168116, 3928499738, 3861593031, 1814928289, 910242415, 342680205, 179168501, 3886219759
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    4178106358, 2547559814, 2214646301, 968430220, 3247518834, 3391453325, 1431785704, 673092023, 2551034805, 3549710365, 3626594117, 4184290734, 2900397496, 1300900446, 2738169122, 1141350978
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vv_i32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1, 2547559814, 2214646301, 9, 1, 3391453325, 3, 9, 2, 1, 3626594117, 4184290734, 2900397496, 0, 2738169122, 1
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
