/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3060690169, 3317857465, 3631855302, 1422550110, 708675499, 672761558, 1016294657, 3821724870, 2960113069, 3226572521, 324331474, 2159288385, 1287405735, 2664430221, 3934146047, 2598382772
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3438983982, 431449372, 34944369, 1693190547, 1660603407, 107569195, 2399056111, 2199170737, 1970568999, 3736843292, 2180467978, 2233498668, 4243460128, 2060673415, 1477929704, 1144739578
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    3344172365, 3463154042, 2015449461, 3736262028, 2040941448, 627890426, 3525615641, 123641348, 1766982243, 3726170654, 203926319, 1111355512, 3563941670, 3947250160, 717334107, 1435288397
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    6499674151, 3749306837, 3666799672, 3115740658, 2369278907, 780330753, 3415350768, 6020895607, 4930682069, 6963415814, 2504799453, 4392787054, 5530865864, 4725103636, 5412075751, 3743122351
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
