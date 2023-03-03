/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1685387102, 2166794544, 4280600076, 355175309, 2305044512, 1057878544, 2892317809, 427916838, 789160909, 3646421124, 2113783737, 2886017179, 2146346344, 1311418821, 2307720588, 3049609970
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3174085501, 1373141223, 1550542733, 3056941292, 16567696, 2022508172, 2057171652, 1589824871, 22005294, 2958571006, 1498415039, 2130816958, 3129862927, 1563896176, 1805427375, 1792091098
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    1138207738, 829900803, 3742319127, 3880137651, 222452398, 848954252, 1547389464, 3462944667, 309943353, 2469941091, 266345662, 3921921446, 1909646988, 2831871450, 1449175203, 1363272483
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1138207738, 829900803, 3742319127, 3880137651, 222452398, 2139568000223461568, 5949994205249550468, 3462944667, 17365717815852246, 10788195813132330744, 3167325340714420743, 3921921446, 6717769850587588888, 2831871450, 1449175203, 5465178879609047060
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
