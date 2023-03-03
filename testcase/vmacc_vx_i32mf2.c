/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3775061928, 679453361, 1522832281, 1143422212, 2145152964, 330000853, 3975223107, 3266719125, 1816987329, 852775557, 2343985948, 3320779988, 1583750198, 3724778138, 2629524668, 531894746
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3218420727, 3678476916, 3762537441, 200807908, 1476510595, 2242234637, 3037230854, 1344431133, 4294746790, 791058777, 4001059318, 1234886072, 2417139559, 1786390519, 2724054258, 3963549421
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    const int out_data[] = {
    3454602373, 30159380, 1557796930, 1989769755, 28624653, 1033005506, 3567691930, 517966215, 562995581, 3450964254, 1378177635, 3135521781, 245374947, 2629895680, 4145987247, 516350613
    };
    const int32_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i32mf2 (data1_v, data2_v, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    12149737558238384029, 2499353503967274056, 5729713475183729851, 229608224342222251, 3167341079270278233, 739939343869150867, 12073670275681835308, 4391878894934484840, 7803500499256419491, 674595592626878043, 9378426819884641099, 4100784958493048917, 3828145255405257629, 6653908353731569302, 7162967872527423591, 2108191113057592679
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
