/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4234766469, 2775831103, 1981155543, 747319210, 3972796501, 1951126085, 1966456185, 2587157038, 3983999937, 760736416, 4035270296, 2725969558, 536654708, 970552733, 3674333481, 1224860316
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    112199137, 1551303018, 916093915, 4114798779, 1911842380, 4220317708, 3663328996, 1554715531, 1639519325, 532652875, 2534109268, 2180769913, 2533639199, 2623168324, 3922052464, 1351296587
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    bool32_t masked[] = {
    1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vuint32m1_t data1_v = __riscv_vle32_v_u32m1 (in1, vl);
    vuint32m1_t data2_v = __riscv_vle32_v_i32m1 (in2, vl);
    vuint32m1_t out_v = __riscv_vle32_v_u32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m1 (uint32_t *out, vuint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    112199137, 1551303018, 916093915, 4114798779, 3972796501, 1951126085, 3663328996, 2587157038, 3983999937, 532652875, 4035270296, 2725969558, 536654708, 2623168324, 3922052464, 1224860316
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
