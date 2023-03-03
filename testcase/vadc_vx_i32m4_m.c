/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    612960102, 2477048680, 294470450, 4135718151, 2018247955, 3160164064, 1277475243, 1660551529, 568642827, 2315359606, 1737071369, 2934952741, 3362175430, 750900554, 2221103169, 1477594993
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    13917110, 236832520, 645552622, 3391329256, 1172463429, 3390891777, 480514955, 4265979233, 3478840814, 2973664667, 978361258, 3993462062, 345777664, 3318179061, 2470867228, 2443293799
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    629903655, 2377281789, 4064320314, 847444499, 3441468200, 3353186807, 142985736, 3738315496, 2294204512, 1264032762, 1758482665, 667556668, 2491726350, 1911971348, 619201210, 2793050766
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    626877212, 2713881200, 940023072, 7527047408, 3190711384, 6551055842, 1757990199, 5926530762, 4047483641, 5289024274, 2715432627, 6928414804, 3707953095, 4069079615, 4691970398, 3920888792
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
