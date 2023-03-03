/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2026647556, 2047777334, 910774548, 2585851596, 1810089738, 1727760667, 4017812891, 3145842265, 1819136548, 1762426817, 522306417, 2808548950, 1029406195, 4100518476, 369128407, 3661247882
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2552567060, 4012577728, 3771076891, 1990363122, 2518630436, 2352369797, 3726081787, 3810661377, 597669517, 2269347386, 3898109054, 188142871, 1737269218, 2703210397, 2349092251, 3976415671
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i32m8 (data1_v, data2_v, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    2552567060, 4012577728, 3771076891, 2585851596, 2518630436, 2352369797, 4017812891, 3810661377, 1819136548, 2269347386, 3898109054, 2808548950, 1737269218, 4100518476, 2349092251, 3976415671
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
