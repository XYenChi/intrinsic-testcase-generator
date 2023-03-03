/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3088791763, 1630519062, 695577334, 1894767701, 4232496228, 2767749266, 663586597, 2092434755, 401186008, 710517649, 3683104851, 2636956273, 1169155899, 2015820159, 3123644258, 2083502652
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2219600521, 2445548860, 2421377046, 1728237857, 3211190030, 3999041317, 468240496, 3104291964, 734929917, 2113021179, 1745958724, 688532721, 2786405604, 1855313635, 1320821293, 3474783218
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    1875875046, 3545599916, 2868507841, 2776334406, 3646502432, 1336739112, 1424418186, 2413846113, 3956258902, 1923337859, 2226084598, 49403174, 1760134372, 1879049482, 2784680677, 3115235912
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    0, 1, 2868507841, 2776334406, 0, 1336739112, 0, 2413846113, 3956258902, 1923337859, 0, 49403174, 2, 0, 2784680677, 1
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
