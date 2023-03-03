/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1498097579, 1145297334, 4227272388, 3179196353, 387655787, 1069017971, 3492944246, 1883861211, 2627933056, 3199858993, 3495931643, 3725509789, 3795181228, 35502910, 2808204865, 3284824119
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2975517738, 1477573727, 630977030, 2860969504, 3656045009, 1081272207, 957927922, 3273074093, 286309661, 2993851621, 2538054005, 1865614118, 1911015273, 3930059115, 3762556492, 4092421484
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    3385212584, 1664146008, 1694461026, 147491975, 955855190, 3369955094, 3475358601, 1945587676, 3171445954, 3950543704, 2635683666, 2803891219, 3952763398, 3327855476, 3305415052, 1186340383
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    5071378776490734136, 1905941986349142672, 7162948307751950088, 468905949016767175, 370542795937484530, 3602542556948994274, 12139233828149559847, 3665217155416035637, 8334347657834055425, 12641182798483930073, 9214169928907643239, 10445924183675642791, 15001453446815092745, 118148553457435160, 9282282629870627980, 3896919503422097577
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
