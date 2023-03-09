/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -168767905, -1765085378, 1935682735, -1772312843, -588791048, -1125626332, 962035801, 1011412718, 1315504360, 1831631675, 1678774417, -358460872, -657828602, -724042527, -1249498023, 2124515681
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -312125611, 2052217522, 301570896, -948186347, 1892912398, -1120943188, -605477895, 2090753317, 1391854818, 690004892, -1449965598, -330941296, 1609899166, -249445993, -508887002, -1141363533
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    bool4_t masked[] = {
    0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m8 (int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -480893516, 287132144, 2237253631, -2720499190, 1304121350, -2246569519, 356557907, 3102166036, 2707359178, 2521636568, 228808819, -689402167, 952070564, -973488519, -1758385025, 983152149
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
