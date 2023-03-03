/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2861555906, 840334642, 1419202919, 2407227920, 3848907521, 1759429973, 1355685156, 1465885082, 3022515453, 2623152433, 1752269573, 3219399958, 133127276, 1062275837, 3827296437, 442712924
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2436731544, 839754988, 1258645612, 2412489420, 343947640, 3288488361, 2905838642, 3698824337, 871163272, 3041121367, 2040475675, 3564634991, 3729539980, 707124710, 3165100915, 1175682513
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u32m1 (data1_v, data2_v, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    424824362, 579654, 160557307, -5261500, 3504959881, -1529058388, -1550153486, -2232939255, 2151352181, -417968934, -288206102, -345235033, -3596412704, 355151127, 662195522, -732969589
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
