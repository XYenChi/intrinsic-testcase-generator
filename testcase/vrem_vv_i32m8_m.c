/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4137130279, 2664444533, 2280576203, 2314683499, 2934775831, 2407315604, 3884544178, 3648645095, 3598332994, 1239157040, 578749575, 2662063852, 633748494, 2207088739, 784704840, 1979397833
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3142394860, 3750780759, 1210997918, 514732273, 32965607, 1449244637, 1876852516, 3129480080, 3828340154, 2321487738, 1518593186, 3600491248, 1164989982, 1857176988, 1447768502, 2429264144
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    3082160130, 3640141480, 1245874271, 3081367336, 1041131885, 2593956526, 34064773, 1313680277, 710530269, 965214223, 2200459482, 486296437, 3962608870, 2258777425, 668699875, 1116843288
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3082160130, 1086336226, 1210997918, 3081367336, 1041131885, 1449244637, 1876852516, 1313680277, 710530269, 965214223, 2200459482, 938427396, 3962608870, 1857176988, 668699875, 1116843288
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
