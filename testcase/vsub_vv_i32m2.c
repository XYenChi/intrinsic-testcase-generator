/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2767278984, 1613827998, 2889701138, 681539248, 2783129981, 4284940901, 3665445874, 4139969674, 2680498211, 2152046163, 3579890426, 843460977, 3737339256, 4022359878, 1337721252, 1568496904
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    4117402717, 1097179993, 4290846557, 2633740083, 1052597461, 985809940, 1844224311, 3953705674, 2052578797, 1414301831, 3279494275, 3637606323, 3754179334, 111515528, 3803742648, 760903445
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u32m2 (data1_v, data2_v, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    -1350123733, 516648005, -1401145419, -1952200835, 1730532520, 3299130961, 1821221563, 186264000, 627919414, 737744332, 300396151, -2794145346, -16840078, 3910844350, -2466021396, 807593459
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
