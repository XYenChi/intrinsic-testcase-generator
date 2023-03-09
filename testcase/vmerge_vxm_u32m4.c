/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1633059429, 2269002033, 2291666291, 1458242443, 1664152955, 1890126471, 2290483993, 3397625401, 3749162152, 1223066139, 4136480536, 2690784966, 4002274215, 1520895392, 1153051469, 4144482613
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    78207336, 910044604, 4049929495, 2871887045, 3682901970, 591433903, 423336630, 1570956264, 3313611604, 4188528672, 3450948108, 4120473080, 2068497696, 3197556900, 2035983269, 1691097892
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    bool8_t masked[] = {
    0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vuint32m4_t data1_v = __riscv_vle32_v_u32m4 (in1, vl);
    vuint32m4_t data2_v = __riscv_vle32_v_i32m4 (in2, vl);
    vuint32m4_t out_v = __riscv_vle32_v_u32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m4 (uint32_t *out, vuint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1633059429, 910044604, 2291666291, 1458242443, 3682901970, 591433903, 2290483993, 1570956264, 3313611604, 1223066139, 4136480536, 2690784966, 4002274215, 3197556900, 2035983269, 1691097892
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
