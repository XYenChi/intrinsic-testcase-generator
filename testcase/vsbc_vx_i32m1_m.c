/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2221563799, 2903210544, 2964492051, 178365886, 1479924377, 63034772, 4099356856, 1661154454, 1553159799, 4201512296, 658128478, 721703796, 157665349, 4262252070, 760329776, 2742821937
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1487352415, 3505736774, 2834784125, 358163712, 4267589411, 1186958128, 2449690090, 4045924319, 1622374376, 3354954175, 1046237669, 3823363225, 856109215, 3851670283, 1276194851, 2735113751
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    3319722524, 3277827165, 1948929048, 2466688156, 2855349333, 3264450071, 1533746854, 1958899770, 3601394310, 1941550381, 2493325440, 806500363, 1062307492, 3728152214, 2852263142, 2889920409
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vx_i32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    734211384, -602526230, 129707925, -179797827, -2787665034, -1123923357, 1649666766, -2384769866, -69214578, 846558121, -388109191, -3101659430, -698443866, 410581786, -515865076, 7708185
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
