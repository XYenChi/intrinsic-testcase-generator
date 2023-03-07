/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2037241052, 1412050612, 1439664654, -587094623, 309449391, -27886729, 1457875539, 77519451, 286531628, -2013160706, -1365434709, 1752636206, 1069493234, -53116257, 1042176596, -1421566517
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -1641438287, 1583247112, 1005341185, 993727219, -2115347277, -569443510, -1761989042, 2054707898, -1479355092, 318912950, -1226259124, 474407702, 1356260137, -1514562775, 14085462, 282851151
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32mf2 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32mf2 (int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3295226126, 1514603411, 1178111098, 262953806, -740988958, -474519577, -402009377, -812860919, -1669681909, -4015166113, -3050774866, 2736481069, 2954702282, -1753550876, 1304626539, -2907627609
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
