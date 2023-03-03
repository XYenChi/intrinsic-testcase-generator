/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2067415650, 3039224679, 2375456779, 3817975290, 2817478941, 751838591, 680595745, 153353198, 3249188509, 1295113336, 2907606550, 879642709, 2200296113, 646712437, 2942937652, 1170259820
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    104100767, 1422047441, 3663303885, 1958026085, 1048022366, 1153757288, 2587190211, 2897724592, 110239096, 662970134, 1223011716, 2032815208, 2652943719, 2166353150, 1752104302, 3669144707
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    3083553849, 1834123583, 1363900393, 1982968098, 2442650658, 3294925578, 2585704170, 355944347, 680515134, 54350564, 3678509858, 2430423217, 3023607696, 828752200, 3430469651, 2804373279
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1963314882, 1617177237, -1287847107, 1859949204, 1769456574, -401918697, -1906594466, -2744371394, 3138949413, 632143201, 1684594834, -1153172500, -452647606, -1519640714, 1190833350, -2498884887
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
