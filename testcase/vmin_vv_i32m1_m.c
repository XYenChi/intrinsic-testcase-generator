/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3509322395, 2909488678, 3295812893, 2533734524, 3470869390, 3245572581, 2486165682, 3250329340, 186622759, 3719894602, 3481797733, 935485241, 3953839573, 1842781017, 4265392857, 4186386427
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3763697942, 165604595, 384568320, 2976042992, 2682302139, 2074730362, 2800671282, 4038549574, 294671596, 3544225749, 959472677, 4276753271, 2988026405, 650547022, 587140623, 2454851201
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    3499071580, 1089180625, 712501747, 515713170, 1384804129, 369071147, 510087106, 1545080865, 2042897181, 2818725301, 1826675925, 800459322, 1173568201, 3228908478, 4141468116, 291770044
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3499071580, 2909488678, 712501747, 515713170, 1384804129, 3245572581, 510087106, 1545080865, 2042897181, 3719894602, 3481797733, 800459322, 1173568201, 3228908478, 4265392857, 291770044
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
