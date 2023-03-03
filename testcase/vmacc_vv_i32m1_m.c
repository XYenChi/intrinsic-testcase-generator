/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    281806204, 2480689108, 3605950341, 2541165505, 2305704007, 443831875, 2372082777, 794310744, 2510743070, 3739737614, 3851009625, 248968126, 1986457802, 1328510371, 1129778971, 1865402014
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    55063344, 1531170409, 235884828, 384599909, 339675356, 1721940136, 909053080, 3927205152, 103931344, 691132644, 4106612735, 4011209581, 63445235, 2990965125, 1200217787, 14986643
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    2327745456, 1446605226, 3982069472, 2388765237, 2430722818, 2462527544, 1219111431, 3512070921, 1640976433, 1272805862, 340527108, 3994089165, 1686447479, 1222435709, 2766916533, 1069009939
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    655973110833609024, 3588577827714078409, 14359144770444089953, 6070247819807549685, 5604527341368931726, 1092948217092665000, 2891833228718923887, 2789675666240275224, 4120070207188069311, 4759959957441093268, 1311373170481414500, 994400894486954790, 3350056752322781158, 1624018517287238040, 3126004113495627543, 1994133293196617147
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
