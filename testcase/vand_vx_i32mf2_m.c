/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3397495299, 1712657854, 4187994495, 389235966, 310605370, 952703430, 948194706, 303106748, 3594905693, 2185772518, 1054666102, 2795885344, 4069539233, 3710114175, 594811098, 2102622044
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2860392278, 3952736190, 982384704, 1967624517, 4076424253, 3924725518, 4179088537, 3960592412, 3693060999, 1037256644, 1215810197, 867919563, 1576115535, 396875559, 234580438, 2359450654
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    4176077154, 1686829038, 9346808, 3389911405, 3731919308, 1877305345, 4099524452, 123689674, 895198127, 1982851252, 2728888887, 2617798945, 1466843586, 3224364861, 3272996758, 3899170544
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1
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
    4176077154, 1686829038, 982384704, 1967624517, 4076424253, 1877305345, 4099524452, 3960592412, 3693060999, 1037256644, 2728888887, 867919563, 1576115535, 396875559, 234580438, 2359450654
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
