/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2489136193, 1029915933, 879521227, 2985578282, 2336061025, 2614142645, 2435715856, 3893140237, 2767795350, 854859364, 1070944719, 2266350135, 360882145, 552385175, 522244562, 2943300279
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3684659286, 3341703618, 1966932189, 3775317350, 3032647537, 2601084395, 1815668771, 2288954468, 1538797417, 1988293712, 1980845296, 985363735, 1962244119, 2896418263, 2277185065, 735560523
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, size_t vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3684659286, 3341703618, 1966932189, 3775317350, 3032647537, 2601084395, 1815668771, 2288954468, 1538797417, 1988293712, 1980845296, 985363735, 1962244119, 2896418263, 2277185065, 735560523
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
