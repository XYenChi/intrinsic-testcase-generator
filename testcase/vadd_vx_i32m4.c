/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3660846934, 2388299849, 1697291112, 2550197658, 2237415784, 3421222392, 1487390962, 992748046, 324178614, 3717349302, 1738628878, 2273433839, 3758688311, 3669528057, 483937535, 2071814239
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2311066832, 2592527629, 163103926, 467935327, 1670253631, 3251142573, 2542748376, 1778119431, 2342623297, 3186029100, 2216821941, 3474725297, 3775017435, 2643671903, 2493548027, 2940016887
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32m4 (data1_v, data2_v, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    5971913766, 4980827478, 1860395038, 3018132985, 3907669415, 6672364965, 4030139338, 2770867477, 2666801911, 6903378402, 3955450819, 5748159136, 7533705746, 6313199960, 2977485562, 5011831126
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
