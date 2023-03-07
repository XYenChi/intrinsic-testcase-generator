/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    478298933, 805626564, -342432265, -1313244683, -1869972172, 1670834861, -822601664, -144897946, -1165404363, 1900997622, -1289619550, -526530364, -379434170, -1002213454, 1261637641, 49588246
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1294879993, 1979402448, 404378718, 396026733, -2028681448, -313473900, 881264013, 1734648700, -925465356, -895480720, -1428917754, 1488641317, -1348320074, 2105093927, -1285205540, 1370315793
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u32m4 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m4 (int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1077417885, 194720454, -2217234498, -1444835805, -1290399265, 3406068432, -1673233349, 700428699, -769869159, 3684214990, -726176932, 503912771, -270779614, -1079022878, -739877418, -442864399
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
