/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1102077926, 2070086678, 1355204486, -1099543330, 611269558, 62389982, -1057354127, 131573726, 1816290389, -606189631, 218127446, -1502328473, -1905864254, 255647481, 1472463898, 1459826667
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -1103962396, 556702186, 1553549983, 1528234635, -699670608, -1351308907, 608206037, -1335377691, -654612760, -1968801403, 998192388, 535222903, 136330050, -9074684, -403155151, -629299542
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int out_data[] = {
    1982253505, 1353938879, 800343589, 364564023, 974688639, -912410220, 664632454, -160509857, 708958882, 1707514478, 686923232, 528473186, 1095341964, -214034373, -1968014191, -49609127
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u32m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m1 (bool32_t mask, int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1982253505, 1353938879, 800343590, 364564024, 974688640, -912410219, 664632454, -160509857, 708958882, 1707514478, 686923232, 528473187, 1095341964, -214034372, -1968014191, -49609126
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
