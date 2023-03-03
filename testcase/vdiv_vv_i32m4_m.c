/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1813698124, 2758041621, 3365069067, 1972215120, 1404540187, 1508855207, 3385201179, 2740389183, 2398114212, 3461187122, 31265454, 2481881978, 4274645383, 894243167, 21200622, 1099452590
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    640573635, 2041617298, 2497489466, 3328728238, 906961431, 1410711125, 4119418880, 816498923, 579543261, 937252121, 3510984619, 2673046532, 2357336187, 1590560778, 3838894655, 90019168
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    3976590491, 470818215, 2318089051, 1678234538, 1002981327, 126460111, 271002563, 4189770013, 1676473249, 3658817717, 1479181607, 3912990771, 429802411, 3777958124, 1863489115, 134976889
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vv_i32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    0, 470818215, 0, 1678234538, 1002981327, 126460111, 1, 0, 0, 3658817717, 112, 3912990771, 429802411, 1, 181, 0
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
