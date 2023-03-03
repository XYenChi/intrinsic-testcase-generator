/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2576299965, 2626086592, 2567917238, 1074947987, 2936624002, 2345750689, 273349011, 3059216071, 4210601275, 4258039020, 3808442495, 1908394031, 2285757234, 3026728489, 1471127480, 3892791129
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2698216948, 2638725967, 647005416, 3107930521, 2603192975, 280632107, 1202675649, 2646125524, 4136816969, 3009037591, 3679530658, 3821580061, 3830393024, 2650812488, 400725736, 239827842
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    1930933418, 846055606, 2011403640, 4182849390, 751339267, 2397332289, 727964887, 1907920804, 670947676, 4288251984, 945219275, 1691679894, 3666438073, 2532995888, 707111597, 1417869478
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    2698216948, 846055606, 2011403640, 4182849390, 2936624002, 2345750689, 1202675649, 1907920804, 4210601275, 4288251984, 3808442495, 3821580061, 3666438073, 3026728489, 707111597, 3892791129
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
