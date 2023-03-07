/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -251643351, 529964284, -1213772571, -1892512395, 1955152976, 136585897, -2009028074, -95741434, -21970718, 733025250, 221955342, -1942609217, -413518509, -2107975510, 1143886055, -1103495474
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -156664696, 875900765, 2022916459, 516436410, 1708694434, -167740005, -1189391584, -1018529246, 1987876263, 42941305, -689941366, 15628346, 789414429, -198728434, 1621572707, -818292056
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int out_data[] = {
    -691051, -2007874749, 488350684, 2037257859, 1436588670, 943574603, 1106027615, -1227702277, 829996736, -995384592, -1919516829, -530210722, 1787054616, 29853964, -1222381355, -24743061
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32mf2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32mf2 (bool32_t mask, int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -691051, -2007874749, 488350685, 2037257859, 1436588670, 943574604, 1106027615, -1227702277, 829996737, -995384591, -1919516829, -530210721, 1787054617, 29853965, -1222381355, -24743061
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
