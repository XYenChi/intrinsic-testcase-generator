/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3552735796, 1318038434, 2973437941, 156058425, 3878933051, 1445988905, 1612846550, 1934779290, 694118492, 2407568028, 4226775235, 2379107069, 4252784372, 1080293470, 628968113, 3434143936
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2573313705, 63322789, 256024500, 96579242, 393142300, 2058980261, 3513600538, 2464252146, 3209492222, 869367064, 2085465864, 1212412459, 2371377526, 3536541796, 520422427, 1789958814
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    3266847819, 2528897972, 3650683542, 1795906679, 621073425, 2749258011, 2029085399, 4073763167, 3538685970, 3600931084, 3885498845, 2841662618, 923305108, 1730980946, 625271740, 1586576839
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3266847819, 1254715645, 2717413441, 59479183, 621073425, -612991356, 2029085399, -529472856, 3538685970, 1538200964, 3885498845, 2841662618, 923305108, 1730980946, 625271740, 1644185122
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
