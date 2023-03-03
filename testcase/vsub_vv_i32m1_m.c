/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3943424433, 1038123704, 2099543481, 2139162860, 1146606308, 236924186, 1188693160, 3223793240, 1290024105, 3823055172, 1659059006, 933824640, 3606866623, 3806096985, 3653589424, 3823314411
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3101176717, 2280537335, 1573516923, 37023353, 10291138, 3184551733, 2045810455, 1272919087, 2842246382, 1397395210, 3920201443, 1294000761, 596172596, 804298936, 3839729275, 881981980
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    720058168, 778981417, 1872326534, 55551413, 1694473935, 794890688, 1011156120, 2852301875, 1689077388, 3915079150, 3611976340, 1990704570, 3732485567, 3333428757, 1658722677, 3094928930
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    842247716, -1242413631, 1872326534, 55551413, 1136315170, 794890688, 1011156120, 1950874153, -1552222277, 2425659962, -2261142437, 1990704570, 3732485567, 3001798049, 1658722677, 3094928930
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
