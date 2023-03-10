/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1804991101, 644872814, 917090164, -358505311, -795800697, 714747199, 152027025, -532482223, -1256329033, 2111393035, 459841551, 78004807, -1646005413, -1892069930, -1657841109, -874154375
    };
    const int32_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int out_data[] = {
    -516604795, -255160184, 224624426, 1293410486, -1386087692, 937884127, 128386992, -1353242340, 424357325, 1620846307, 735363477, -1836453050, 1718581485, -1200967113, -616940388, 1221545289
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, in1, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vneg_v_32mf2 (mask, data1_v, vl);
        void __riscv_vse32_v_i32mf2 (bool32_t mask, int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -1804991101, -644872814, -917090164, 358505311, 795800697, -714747199, -152027025, 532482223, 1256329033, -2111393035, -459841551, -78004807, 1646005413, 1892069930, 1657841109, 874154375
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
