/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4102074132, 3406827819, 4269271087, 1090558829, 3095098577, 4065619810, 1295810472, 1013349708, 3267361008, 3934294000, 1068872529, 3062841954, 563340241, 1040317094, 3819206306, 2182896922
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3312041133, 3212739318, 3392933167, 4111800876, 2294743989, 1068944046, 304993578, 711815144, 1801076380, 475431878, 78427836, 3460636197, 4165119141, 3055128040, 892252801, 957843547
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    1015581771, 1894489911, 3816279291, 2927128709, 2501012209, 2480049452, 3041709210, 3036281902, 2475899840, 875251511, 1245496345, 1663904759, 3800204288, 3893986816, 2369110583, 410030799
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vx_i32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    790032999, 194088501, 876337919, -3021242047, 800354588, 2996675764, 990816894, 301534563, 1466284628, 3458862121, 990444693, -397794244, -3601778901, -2014810946, 2926953505, 1225053375
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
