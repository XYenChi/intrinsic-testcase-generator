/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1834696433, 3160494105, 1968340624, 3066869612, 1448149348, 4096069489, 3612959402, 840966114, 3688775269, 3961884675, 614095203, 40019561, 3006250677, 2039864585, 3600164242, 694104013
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    50472075, 4093769566, 1515732105, 3438420483, 2294865489, 1351513510, 12040686, 3320367634, 2638595465, 115037685, 3910942247, 410332776, 3338827364, 917416348, 545028819, 1375774768
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i32m8 (data1_v, data2_v, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    50472075, 933275461, 1515732105, 371550871, 846716141, 1351513510, 12040686, 797469292, 2638595465, 115037685, 226371029, 10137166, 332576687, 917416348, 545028819, 681670755
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
