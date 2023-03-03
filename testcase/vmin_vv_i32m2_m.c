/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1346107988, 101885077, 3076763862, 3300311421, 698596692, 504471596, 1299866799, 4293285519, 4074987666, 1323372368, 1676327321, 3094852840, 1108030917, 587800895, 2917819316, 3013696686
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2855860330, 682151840, 1148019255, 3689813082, 3680180698, 3276316687, 184357256, 480071367, 2370196677, 1483384502, 468248364, 3062073563, 2515338944, 3305602098, 3523054530, 378485829
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    2735267989, 3118249269, 766789001, 2995157466, 1998113967, 3408678393, 1395953287, 601947660, 1873163578, 3843612688, 2109716542, 259804169, 2189684735, 3939188083, 2243740496, 374591660
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    2735267989, 682151840, 766789001, 3689813082, 3680180698, 3408678393, 1299866799, 4293285519, 1873163578, 3843612688, 1676327321, 3094852840, 2189684735, 3305602098, 2243740496, 374591660
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
