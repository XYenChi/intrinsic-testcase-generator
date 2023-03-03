/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    66857410, 847688959, 3667804490, 325149302, 4231585092, 890862048, 3930419858, 4158679949, 3543031778, 599046636, 2945891024, 2428366151, 2024240438, 2188509970, 734958893, 2332344935
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    279345787, 318038248, 2731962351, 2274404071, 2977755252, 992408215, 2680729559, 2863611570, 926643914, 2185158392, 374690127, 3590661755, 4222204451, 1593747713, 458580024, 3279745286
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    1838188494, 828695134, 482921006, 1351409086, 494322372, 1905827874, 2582257294, 583516084, 2988202435, 1289520948, 3760493317, 1447386887, 4140462878, 3613730420, 2818283359, 1626902455
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1838188494, 318038248, 2731962351, 323508259, 494322372, 1905827874, 2680729559, 583516084, 2988202435, 388018484, 374690127, 1162295604, 173723575, 3613730420, 2818283359, 947400351
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
