/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2361278102, 3930819988, 2684073155, 2917221490, 4225247840, 3762178321, 2356043171, 160853369, 3752366886, 1065326378, 3148167576, 3623715086, 4233781605, 598270592, 348701986, 61493805
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1501837038, 1490726296, 3638666137, 403340354, 3500511018, 470503388, 2541694450, 2434291354, 1004114663, 2630555622, 3785289022, 2394118606, 2366334000, 4055914291, 3259918023, 1914430617
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    const int out_data[] = {
    398344222, 1348853618, 1304616915, 1583884720, 2768014232, 942792886, 3472037445, 503526786, 3115643075, 3529327805, 976746709, 454323087, 2262055305, 2866179044, 3518854427, 3163663687
    };
    const int32_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i32m2 (data1_v, data2_v, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3546254911000286098, 5859776722302858066, 9766446099633869150, 1176633150056892180, 14790526620468715352, 1770117647233444434, 5988341855163138395, 391563965921998412, 3767806614303892493, 2802400296442124921, 11916724165825897381, 8675603710689813203, 10018541362748125305, 2426534246844009316, 1136739892336148105, 117725626211491372
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
