/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1880783365, 2687320182, 4147847255, 885756072, 1669511339, 3772524725, 2076652732, 494325757, 3023614240, 933156040, 4192498842, 3651235532, 4266615634, 2456150496, 1684180576, 4051587231
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    468213380, 3963049416, 4131110203, 1389551375, 3978448213, 1102319633, 4131120785, 2515364079, 3545879546, 2506272781, 246619590, 3974859045, 2385378933, 1735425978, 2102109597, 434628779
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
        out_v = __riscv_vmin_vx_i32m4 (data1_v, data2_v, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1880783365, 3963049416, 4147847255, 1389551375, 3978448213, 3772524725, 4131120785, 2515364079, 3545879546, 2506272781, 4192498842, 3974859045, 4266615634, 2456150496, 2102109597, 4051587231
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
