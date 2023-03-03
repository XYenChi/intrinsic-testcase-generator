/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4228460126, 3021650665, 1421127208, 4183381101, 3740902913, 3524706155, 2717216135, 2800520166, 379061014, 370098853, 408237401, 1687711861, 848454206, 3071640445, 2970518390, 1784192741
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    773770347, 388183669, 3722210602, 4053434436, 3632462753, 773395012, 732337965, 2927043960, 3772183845, 74532597, 2111203860, 1392517276, 1607224508, 954877815, 3589184097, 2206498533
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
        out_v = __riscv_vsub_vx_u32m4 (data1_v, data2_v, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3454689779, 2633466996, -2301083394, 129946665, 108440160, 2751311143, 1984878170, -126523794, -3393122831, 295566256, -1702966459, 295194585, -758770302, 2116762630, -618665707, -422305792
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
