/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    14794513435232888227, 15831199127100972650, 8965827644151256849, 13586322888608093357, 12745877528523186461, 15441038607076877729, 8289579357709114995, 12164391640383658284, 1774425878571039933, 1395706400001825693, 13184150397995680782, 4811650976970461252, 7082672347833694662, 6350878123016014722, 6545199234163830976, 2991163609533816719
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    2758474944360576103, 8301786831837743905, 16939413390901495418, 8014256156090576779, 5223354119360710456, 901880112039756330, 7523922724169893035, 10851703873320633320, 13299539458720440685, 5952251765365452472, 8909706900027835741, 3898695824576332324, 10641873354159544763, 12072545354708617106, 17126633032971560562, 6157984734948126395
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m4(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4 (*in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4 (*in2, vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i64m4 (data1_v, data2_v, vl);
        void vint64m4_t __riscv_vse64_v_i64 (int64m4_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    14794513435232888227, 15831199127100972650, 16939413390901495418, 13586322888608093357, 12745877528523186461, 15441038607076877729, 8289579357709114995, 12164391640383658284, 13299539458720440685, 5952251765365452472, 13184150397995680782, 4811650976970461252, 10641873354159544763, 12072545354708617106, 17126633032971560562, 6157984734948126395
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
