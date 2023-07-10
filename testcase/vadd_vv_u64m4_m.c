/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    3258686279622638124, 15728117887844560099, 1529959956041295728, 3082830391613083685, 3482146366406912216, 3905410273134372841, 6109754128675650781, 15658712670402974626, 14424121437642623294, 15771371138486101959, 3346252326575308164, 10363702432561551454, 11890111455926737225, 9300453110419723819, 9040256354981599825, 3070883499418386493
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    13818869241549246997, 1182630071677876314, 2428962107077493055, 16312116507690361473, 13029117932825138390, 8929875273748716617, 3148857798328643206, 14067989920382654506, 9284462777984893355, 2045597383634075549, 1765737418218698872, 13941034961552080727, 6523371956967874072, 2816811932972923310, 6168117638854880502, 6887249724086706350
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const uint out_data[] = {
    0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1
    };
    const uint64_t *out = &out_data[0];
    uint16_t masked[] = {
    0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1
    };
    const uint16_t *mask = &masked[0];
    vuint64m4_t data1_v = __riscv_vle64_v_u64m4 (in1, vl);
    vuint64m4_t data2_v = __riscv_vle64_v_u64m4 (in2, vl);
    vuint64m4_t out_v = __riscv_vle64_v_u64m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_u64m4 (uint64_t *out, vuint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    0, 16910747959522436413, 3958922063118788783, 1, 0, 0, 9258611927004293987, 0, 5261840141917965033, 17816968522120177508, 0, 5857993320404080565, 0, 12117265043392647129, 1, 9958133223505092843
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
