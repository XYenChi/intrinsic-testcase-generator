/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2307116998, 2596039704, 3017780849, 2708567371, 1656272736, 1730215490, 1797494284, 194438477, 2603129178, 2884572251, 1680401433, 3607040477, 197339638, 2922645025, 26540502, 2075087992
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2245560754, 3810924527, 4018392087, 3996849212, 3888416653, 770522324, 1222951670, 2713861572, 3312029554, 3911826495, 2903480746, 2329228132, 4005495195, 23400294, 3098236607, 1899006307
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    3844489301, 2056281456, 3769999480, 1628508339, 2418947427, 3707229137, 574837889, 3082505529, 3429527633, 3097296998, 89073, 1834949951, 3926642494, 3251903704, 3120412004, 2936261667
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vv_i32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    0, 1, 1, 1628508339, 2418947427, 3707229137, 0, 13, 1, 3097296998, 1, 1834949951, 3926642494, 3251903704, 116, 0
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
