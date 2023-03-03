/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1154525689, 2900201213, 463480750, 3737527665, 2200033960, 706892776, 2454369304, 3758328626, 1201062877, 3400317565, 1237915526, 3378077751, 2401995974, 3550476874, 4006694800, 2705410655
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    918944791, 3802967396, 4149803045, 3595825010, 1727164258, 2234871809, 1649238408, 102343488, 483597892, 669540059, 1143329087, 1726893508, 4060867963, 3433422769, 85362631, 1180781945
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i32m1 (data1_v, data2_v, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1154525689, 3802967396, 4149803045, 3737527665, 2200033960, 2234871809, 2454369304, 3758328626, 1201062877, 3400317565, 1237915526, 3378077751, 4060867963, 3550476874, 4006694800, 2705410655
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
