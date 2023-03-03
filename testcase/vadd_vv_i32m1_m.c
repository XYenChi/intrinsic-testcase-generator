/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3611914231, 4196738627, 1979866505, 2844929646, 2283001503, 3089014890, 2512596436, 1828830211, 3445319865, 1218871388, 142375876, 2247391928, 2898535819, 573965858, 2530164050, 919405416
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1050675922, 3343191173, 3256513476, 1655731174, 1249785119, 3923508183, 2007594832, 2481146376, 1231795435, 1254349447, 1087811492, 44527496, 2142234979, 2988267678, 2296899192, 2753477100
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    511768877, 3974416829, 3947776428, 3940298313, 1283895616, 4033318975, 3857841384, 625972890, 600871607, 11469592, 42274029, 4152343584, 4006994393, 2943170674, 2495725001, 3392760249
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    511768877, 3974416829, 3947776428, 3940298313, 3532786622, 4033318975, 3857841384, 4309976587, 600871607, 2473220835, 42274029, 4152343584, 4006994393, 3562233536, 4827063242, 3392760249
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
