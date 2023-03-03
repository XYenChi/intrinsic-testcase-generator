/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1485922380, 2367033210, 4124118404, 3537328084, 3409452042, 2226505913, 3630147959, 2456002200, 2763119529, 287134151, 3199463632, 2799354842, 1453668204, 1518153649, 2603225339, 2539566244
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1067774304, 2269153609, 3629529411, 2575131736, 3889195622, 716400421, 2816692606, 1209029804, 987092118, 1441352768, 3819625621, 2104412483, 613601269, 3261018715, 1931235119, 635781567
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i32m2 (data1_v, data2_v, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    0, 0, 0, 0, 1, 0, 0, 0, 0, 5, 1, 0, 0, 2, 0, 0
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
