/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2277455162, 2155092817, 2023823068, 1591003372, 956108413, 2155747379, 3209799903, 948889628, 3727496640, 1425301086, 1548363587, 3445476261, 1750836335, 4048651970, 3238947772, 488264399
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    4120494908, 2134800934, 3248832398, 1858206719, 1979417345, 3358172688, 836822935, 1173233659, 1546848801, 1259071737, 2151584848, 3666098471, 444807017, 2510627532, 1806547463, 579442916
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i32mf2 (data1_v, data2_v, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1, 0, 1, 1, 2, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1
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
