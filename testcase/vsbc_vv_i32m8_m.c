/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    442095832, 696614245, 3534553213, 3770251556, 471465112, 2089356907, 1783109369, 4248935468, 636671939, 2567659202, 173447392, 2713185599, 3257047453, 778049544, 3138561214, 1634546131
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    80584376, 3782978655, 456507050, 1093402938, 2023526068, 2414882016, 3415667978, 2986415589, 897439073, 2030012259, 1458791505, 3830763746, 335552224, 2740901386, 1079749101, 3818824075
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    400628829, 1063629099, 980917088, 237345468, 3388111814, 2196946191, 805390712, 3303287159, 1030220549, 1620532146, 2657069168, 1373597087, 2911734331, 3673532345, 3475228002, 2249081164
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    361511455, -3086364410, 3078046163, 2676848618, -1552060956, -325525109, -1632558609, 1262519879, -260767135, 537646943, -1285344113, -1117578147, 2921495228, -1962851843, 2058812112, -2184277944
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
