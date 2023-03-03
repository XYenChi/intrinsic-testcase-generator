/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    984379644, 3559994151, 3270537033, 781942176, 4115157482, 3589469454, 1384739265, 3307678234, 380132038, 28415952, 2019508033, 2989784889, 1939713055, 247051268, 3812221240, 3552490975
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2835385603, 236773028, 489734439, 2102958028, 4275575033, 3054323720, 3400104019, 954689507, 2195170521, 4212114687, 422489006, 251840431, 3730879374, 4207408307, 977748161, 1659428381
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    434069468, 1808670848, 644030613, 3617618920, 1170747588, 3465546038, 602228175, 2314843341, 1582832442, 823345089, 3205184202, 3510651235, 1911751217, 3537097535, 2072676183, 1747042539
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3819765247, 1808670848, 3760271472, 2884900204, 8390732515, 3465546038, 4784843284, 2314843341, 2575302559, 823345089, 3205184202, 3241625320, 5670592429, 4454459575, 4789969401, 1747042539
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
