/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -859728035, -1864984518, -1737608831, -1734549565, -1908774660, -1174631466, -216383286, 461405258, 1173588650, 537657198, 1304561299, -376548615, -898543935, 5095934, -1456549808, -788626246
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    636591605, 456186785, -628743431, -673159239, -776270881, -1160373068, 340305897, 1360483008, 1760957988, -1815244962, 1960225991, -1288527005, 36980249, -1011383667, -1951864328, -178731507
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u32m1 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m1 (int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    -2260544249, -2502720334, -699064161, -984620259, -2347818899, 407919058, 627312807, -1322344379, 186503382, 799986299, 2129661555, 245806416, -1987554932, -1926691992, 330235475, -1357487897
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
