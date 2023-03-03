/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3038034176, 715125412, 3403410785, 3656572986, 893877257, 1493958489, 935269872, 2551195456, 3411367433, 1636379067, 2291228904, 2013674895, 149621271, 1469547021, 881889201, 3566289799
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2836400862, 3150778210, 3820245002, 1006703948, 1351274565, 4255422528, 2152247136, 3450742471, 488646717, 3379640418, 1676240078, 2987753236, 2755444686, 3283696191, 3501967641, 1312359358
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    bool16_t masked[] = {
    1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vx_i32m2 (data1_v, data2_v, size_t vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    2836400862, 3150778210, 3820245002, 3656572986, 1351274565, 4255422528, 935269872, 3450742471, 3411367433, 3379640418, 2291228904, 2013674895, 2755444686, 3283696191, 3501967641, 1312359358
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
