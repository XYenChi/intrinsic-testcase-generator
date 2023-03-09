/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    5415838984783481919, 6117236856917884892, 5742395772057827228, 12832096692054314093, 8179276450035554304, 12223871745028101090, 10696272490121804336, 1174798963915348488, 3730754343873678599, 1944386059932441395, 9269736417343329012, 9692778074208994940, 12057560987011607594, 6044366654102781519, 14300722572510469579, 11261764576272614906
    };
    const int64_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vuint64m8_t data1_v = __riscv_vle64_v_u64m8 (in1, vl);
    vuint64m8_t out_v = __riscv_vle64_v_u64m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_x_u64m8 (src, vl);
        void __riscv_vse64_v_u64m8 (uint64_t *out, vuint64m8_t out_v, size_t vl);
        in1 += 8;
    int64_t golden[] = {
    5415838984783481919, 6117236856917884892, 5742395772057827228, 12832096692054314093, 8179276450035554304, 12223871745028101090, 10696272490121804336, 1174798963915348488, 3730754343873678599, 1944386059932441395, 9269736417343329012, 9692778074208994940, 12057560987011607594, 6044366654102781519, 14300722572510469579, 11261764576272614906
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
