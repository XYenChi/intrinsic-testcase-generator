/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    14643332588854850833, 11127515931461880923, 8964648901469471541, 12367458482829235450, 10861098880575610031, 16087709693239520648, 8187345621581361788, 11313205184492513286, 18372639375052458411, 12695851813577926093, 11820430663643275990, 6805861122715599511, 13739755292378921571, 6974481697734879877, 8927338606670695881, 6985222171725999327
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    11003094336451119820, 4512200115495789198, 18072177344623484386, 552113124435154633, 16422769423950452598, 13564604539858109414, 2983502548447089238, 13607817228121745456, 11974408936691083926, 14399986778558139236, 2711012066289526178, 15411753558404489963, 8635284264352118571, 7071999121645638525, 215671383635016565, 16148728338413849588
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m8(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8 (*in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8 (*in2, vl);
    vint64m8_t out_v = __riscv_vle64_v_i64m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u64m8 (data1_v, data2_v, vl);
        void vint64m8_t __riscv_vse64_v_i64 (int64m8_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    3640238252403731013, 6615315815966091725, -9107528443154012845, 11815345358394080817, -5561670543374842567, 2523105153381411234, 5203843073134272550, -2294612043629232170, 6398230438361374485, -1704134964980213143, 9109418597353749812, -8605892435688890452, 5104471028026803000, -97517423910758648, 8711667223035679316, -9163506166687850261
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
