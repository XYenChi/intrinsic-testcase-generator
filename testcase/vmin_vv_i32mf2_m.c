/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3785978676, 1869351028, 1450171302, 2345625871, 2670193834, 3720761238, 3260930605, 1641128753, 1481568058, 2999131883, 319712067, 2619449973, 1257929350, 1204472805, 1340626131, 1286371048
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2665281570, 132115790, 803830378, 2066140497, 3154667116, 2567560334, 4032861169, 583786232, 2835999875, 1649804986, 4119550701, 2388415072, 1668650676, 2270219165, 3155045762, 3568050180
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    57680898, 3376333777, 3810399733, 2188637600, 3239234287, 435369254, 3224261836, 3070161485, 2097338399, 2240835752, 113523206, 2345287317, 2440855391, 2684843984, 1788603273, 110765966
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3785978676, 1869351028, 1450171302, 2345625871, 3239234287, 3720761238, 3224261836, 3070161485, 2097338399, 2999131883, 113523206, 2345287317, 1668650676, 2270219165, 3155045762, 3568050180
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
