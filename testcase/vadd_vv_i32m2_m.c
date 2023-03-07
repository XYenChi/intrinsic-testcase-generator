/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -125086066, 411824741, -984867811, -238519695, 613851230, 204852790, -1138772818, 1922964659, 205533505, 1182795478, 2098717735, 383252460, -1959259605, -121689578, -876379452, -1980365694
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -971804860, -1239946054, 1014990065, 781487755, 1756647095, 1238419629, 82212146, 1196913698, 1499747868, -39375866, 610383146, 1728588677, -340564665, -1786450029, -1596345326, 838430906
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int out_data[] = {
    -1141127340, 1447719175, 295363174, 1066449, -1208436154, -79175019, 2100365817, 1748715727, 1075925244, 2038197863, -2073251529, 511670782, 1299077160, -586179069, 2051645877, 2144289032
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m2 (bool32_t mask, int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -1141127339, 1447719175, 295363174, 1066449, -1208436153, -79175019, 2100365817, 1748715727, 1075925244, 2038197864, -2073251528, 511670782, 1299077160, -586179068, 2051645877, 2144289032
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
