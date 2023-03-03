/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3893947543, 891461725, 3818713579, 48617676, 3069993147, 471320020, 1444621585, 3660223482, 1774023906, 134270948, 227694170, 4195684771, 1421773913, 1556217354, 3140244419, 2563362907
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2292731360, 2317798693, 58545968, 4113605511, 645951837, 3121779225, 2151282630, 778391797, 1636095337, 3495728391, 3551577442, 3303140599, 463233223, 729797377, 4238087794, 4213965378
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
        out_v = __riscv_vmin_vx_i32mf2 (data1_v, data2_v, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3893947543, 2317798693, 3818713579, 4113605511, 3069993147, 3121779225, 2151282630, 3660223482, 1774023906, 3495728391, 3551577442, 4195684771, 1421773913, 1556217354, 4238087794, 4213965378
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
