/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    344614104, 426886031, 793824091, 3410054967, 2160969847, 744620229, 3386089784, 3060689382, 1772593029, 426903311, 2529101879, 2631924628, 714851091, 2251490732, 3877224329, 1365581567
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    266865724, 1734235951, 3225833782, 690999672, 2480701595, 12512553, 3850973101, 3755915578, 374912563, 3651898206, 2020724092, 3205607043, 572450519, 3799509883, 1245671508, 1457936517
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    4078815099, 2957110442, 1493944282, 3377967611, 1086035205, 3960902542, 1813721077, 282934645, 1472152036, 3123459263, 386150471, 4167230652, 1794822334, 790394429, 2749080574, 2263903229
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    77748380, 2957110442, -2432009691, 3377967611, 1086035205, 732107676, 1813721077, -695226196, 1397680466, 3123459263, 508377787, -573682415, 1794822334, 790394429, 2631552821, 2263903229
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
