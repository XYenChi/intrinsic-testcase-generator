/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1030374995, 1778427603, 3670178949, 3165401766, 4012211125, 3438204816, 2481360343, 3513004461, 3453061104, 3049640241, 3094719421, 777412195, 3565095211, 2720555282, 4197440785, 3108933673
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3453730582, 2505488189, 2299295821, 3823681847, 3495494603, 2684297899, 3416302784, 2725084543, 1086823764, 2373499919, 4165512797, 3467511323, 35616467, 1446479298, 3917146008, 3469497643
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i32m4 (data1_v, data2_v, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    362605597, 727060586, 2299295821, 658280081, 3495494603, 2684297899, 934942441, 2725084543, 1086823764, 2373499919, 1070793376, 357862543, 35616467, 1446479298, 3917146008, 360563970
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
