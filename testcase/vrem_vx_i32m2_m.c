/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    441664046, 3802276775, 2793293752, 2112867828, 3385373417, 3509229157, 3363463772, 3848260523, 2607479236, 2919879297, 2366184627, 3814260379, 1452459980, 2901151473, 3196115466, 3222057187
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1112075146, 3850491102, 243553440, 3475102919, 1202287631, 3045815548, 2966955079, 691478338, 236487515, 2102725015, 875623818, 2409723441, 912170800, 493579104, 2329618194, 2769956647
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    3063071455, 2167520091, 3762114590, 2992908171, 1607980782, 306175225, 405397061, 3739378165, 3094901331, 3450966452, 1448491876, 44677413, 1128084251, 2115403451, 2066648741, 1281174617
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    228747054, 48214327, 243553440, 2992908171, 1607980782, 3045815548, 405397061, 691478338, 3094901331, 2102725015, 1448491876, 44677413, 1128084251, 2115403451, 2066648741, 2769956647
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
