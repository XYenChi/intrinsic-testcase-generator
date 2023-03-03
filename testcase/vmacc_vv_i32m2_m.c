/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    380779096, 2053616961, 2731287777, 2980323126, 4116124691, 378070325, 2536158272, 4069344876, 864349050, 293928531, 1734340247, 2379307871, 2054735855, 1307732798, 1251415539, 3920529279
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1707578953, 1144637586, 795856851, 2967157586, 1309465917, 4102777225, 473972603, 1378604855, 3638872372, 3062276197, 3193356292, 1381007029, 1409084081, 1043259997, 1330538, 2913246252
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    2011221709, 387394271, 875855180, 2110694027, 4163126258, 1126860006, 2427429475, 3030083123, 1740900610, 70890468, 2299130070, 2479702794, 1995819201, 2679045488, 2912638882, 970912537
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    765831184208595064, 795559445519830432, 2392212547556134861, 6290550220578168403, 17135946782304236278, 426032328697921951, 6156345342717867200, 12330453230434127748, 1504745788397920501, 20836731121142509, 3987473813488927290, 5899976375504891574, 4100881272392151855, 3503475651991515425, 3644921556430387399, 3806491028656670823
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
