/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1492036610, 286750294, 1396513977, -1584111453, -2130704642, -545821321, -734523047, 1664047969, -1015765190, 1018948730, -824523558, -1636171552, -1903943890, 1915877439, 551472041, -879969330
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -1216465924, -1920712313, 90447462, 1840110105, 395706239, 314294890, -524037354, 1360784684, -2033263783, 519652949, -406145729, 1551793434, 633432680, -693105423, 904882785, 1332589876
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    bool64_t masked[] = {
    1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32mf2 (int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -1216465924, 286750294, 1396513977, -1584111453, 395706239, 314294890, -524037354, 1664047969, -1015765190, 1018948730, -406145729, -1636171552, 633432680, 1915877439, 551472041, -879969330
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
