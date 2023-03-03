/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2184898792, 2133414750, 3512688660, 3337662151, 3898144076, 106282062, 563477947, 1804327919, 1945449993, 1532923248, 1046126801, 1891565050, 2029254161, 1331800324, 3781857747, 2803957649
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2945814652, 3153235131, 654400186, 3191915595, 3669469392, 3114271702, 2535301123, 1252005814, 405271275, 2769083833, 3688173015, 791843904, 3479818016, 120867262, 1368623586, 2223434185
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    3848021990, 2591667954, 2574747793, 2414852171, 3622029372, 3148142242, 2127710592, 1968673698, 1880990704, 3729477837, 719087108, 1433924148, 1488805176, 2976814226, 2269342560, 2493276949
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3848021990, 6727158338693582250, 2574747793, 2414852171, 3622029372, 3148142242, 1428586271814834481, 2259029044950521066, 1880990704, 3729477837, 3858296637716475015, 1433924148, 1488805176, 2976814226, 5175939711441020742, 2493276949
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
