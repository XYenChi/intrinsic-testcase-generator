/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3410065034, 2769195160, 4283923205, 824595275, 2653403965, 2759598207, 3656139437, 1686844784, 3214961072, 3897615814, 3583919569, 1148319563, 150963730, 597000037, 265223746, 3876975773
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    4009098909, 2838974784, 2590271748, 1648321828, 11240501, 1808447099, 2645022514, 1315030002, 3561250685, 2420332531, 925488591, 1352816701, 4148021234, 3702729608, 4012599272, 219296818
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, size_t vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    4009098909, 2838974784, 2590271748, 1648321828, 11240501, 1808447099, 2645022514, 1315030002, 3561250685, 2420332531, 925488591, 1352816701, 4148021234, 3702729608, 4012599272, 219296818
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
