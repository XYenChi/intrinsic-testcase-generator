/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1791925691, 2894933676, 743726941, 3351082496, 329260034, 2875218829, 2082255514, 1304861100, 2927985865, 985940496, 993872609, 3612968612, 1129388504, 3026495479, 2841943276, 1369083716
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1000334337, 1328258585, 1009487026, 667123675, 2057120721, 92660991, 766235892, 3958722298, 1771172424, 952000212, 2362345479, 3705129983, 3361512127, 2913989616, 2992241645, 2256820583
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    3738710959, 3715335290, 3085745464, 2108654858, 1859871640, 4158805962, 1983583794, 3334602985, 1234672359, 4160229650, 169354938, 2887661048, 2001935823, 1027955845, 2501873063, 2745826829
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    791591353, 1566675090, -265760086, 2683958821, -1727860687, 2782557838, 1316019621, -2653861198, 1156813441, 33940284, -1368472870, -92161372, -2232123624, 112505862, -150298369, -887736868
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
