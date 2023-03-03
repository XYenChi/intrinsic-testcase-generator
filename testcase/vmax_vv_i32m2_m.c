/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1066419763, 2309689136, 1862482441, 2379569728, 4197755609, 347405094, 2251815385, 2426186535, 2573266443, 1182682685, 3156075506, 1672772222, 957830090, 3986090253, 974301064, 1168783052
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    478170684, 519139782, 413103298, 2343931697, 787340414, 2096843079, 2636905543, 2507632731, 3790016220, 1280010739, 837512561, 3087488768, 217800647, 2111426326, 3081491165, 2144529709
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    3140997128, 4202562170, 611006856, 2012115575, 2710611580, 401987214, 2423987636, 3061368196, 2448907652, 1047437350, 3405708494, 1455360291, 2342804075, 2404932108, 3074905916, 342828153
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3140997128, 4202562170, 1862482441, 2379569728, 4197755609, 401987214, 2636905543, 3061368196, 2448907652, 1280010739, 3156075506, 3087488768, 2342804075, 2404932108, 3081491165, 342828153
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
