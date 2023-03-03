/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1072871617, 2312653185, 2247244695, 1844073922, 1175926761, 501515529, 2965851823, 3350014376, 3412698657, 711068455, 2612434421, 3635481108, 3697971510, 2296868960, 3917710598, 1681947908
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2652855385, 3603228755, 3570662305, 4088870006, 740194247, 1383236269, 1548118969, 319670262, 1051257853, 527740185, 3023939196, 3988312172, 3755789083, 870932543, 1474529361, 3584619108
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    529783446, 819352437, 1531469149, 2388561783, 475805279, 2778913303, 2640701045, 3867855342, 1111302575, 3670092541, 2528225254, 1202742785, 1315277772, 4079112760, 3091240883, 767624694
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    529783446, 8333018456534334675, 8024151922547721975, 2388561783, 475805279, 2778913303, 4591491466429530487, 1070899973279686512, 1111302575, 375259397989364175, 2528225254, 14499433554112446576, 13888801026503025330, 2000417924270565280, 3091240883, 767624694
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
