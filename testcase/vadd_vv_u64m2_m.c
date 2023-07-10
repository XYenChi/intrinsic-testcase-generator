/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    11979300842007037747, 13575275298005239722, 8095867733671233149, 10278137977446426735, 4786470185677124310, 2946965576605070155, 6299830092927596090, 6003680943554341214, 7833465782953444940, 2955943187372236579, 5269558175766597248, 10721289860145414812, 11977690255687061584, 15578573005557358516, 6161660754085973980, 11227276341269699396
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    6275511741660146388, 13020456902890643597, 3678700514720747020, 12513488543405977946, 2576478943161787973, 5538903660905535622, 6652814910761153083, 8744168667940823584, 13376429714215722790, 5622848363806925077, 4313762108222568211, 5865261765429055870, 4746825331079610789, 17962255198794842926, 14861174999511780942, 15899364921647204855
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const uint out_data[] = {
    1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0
    };
    const uint64_t *out = &out_data[0];
    uint32_t masked[] = {
    0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0
    };
    const uint32_t *mask = &masked[0];
    vuint64m2_t data1_v = __riscv_vle64_v_u64m2 (in1, vl);
    vuint64m2_t data2_v = __riscv_vle64_v_u64m2 (in2, vl);
    vuint64m2_t out_v = __riscv_vle64_v_u64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_u64m2 (uint64_t *out, vuint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    1, 1, 1, 4344882447142853065, 7362949128838912283, 1, 0, 0, 1, 8578791551179161656, 9583320283989165459, 16586551625574470682, 16724515586766672373, 15094084130642649826, 1, 0
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
