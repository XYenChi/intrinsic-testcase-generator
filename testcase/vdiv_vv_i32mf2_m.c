/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1208319936, 2691966014, 4093036624, 1340261451, 3917545797, 2466229320, 2702229185, 3600904213, 1041931948, 2865772206, 1429637240, 2254412992, 1729759710, 2034830585, 3036310377, 2821732401
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3694681615, 1413988263, 823398474, 3527024398, 1971393128, 3298597273, 662676868, 1156998267, 3994591485, 4288835723, 2645337388, 3676125436, 588977811, 3597660142, 2168957368, 3921289513
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    303469630, 231062091, 4113824989, 474302328, 2076921465, 2150195417, 4250439241, 2670094841, 1296364765, 1465558789, 2725434685, 1229014614, 1964614652, 3553063166, 3834653460, 3753138625
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vv_i32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    303469630, 0, 4113824989, 2, 2076921465, 1, 4250439241, 2670094841, 3, 1465558789, 1, 1229014614, 1964614652, 3553063166, 0, 1
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
