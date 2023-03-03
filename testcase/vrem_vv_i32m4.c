/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3104581634, 3138561638, 3745587794, 921636035, 504227994, 415091681, 4212771146, 3073367465, 2641289359, 3027252438, 1676927736, 3568600588, 3409985913, 2309625146, 2615417079, 3363026624
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2864870405, 2683240165, 1174716857, 1946149189, 2964883150, 1687771262, 909445603, 3066243391, 2670537061, 3595400061, 3379812936, 2059138588, 459231114, 1729724119, 3464445715, 326988920
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
        out_v = __riscv_vrem_vv_i32m4 (data1_v, data2_v, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    2864870405, 2683240165, 1174716857, 102877119, 443743180, 27404538, 909445603, 3066243391, 29247702, 568147623, 25957464, 2059138588, 459231114, 1729724119, 849028636, 326988920
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
