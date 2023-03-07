/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    347884173, -1659360476, -396640589, -74824740, 1095345918, -81933718, -123739710, 1469430681, -1630394521, 1684946992, -789030241, -1809086085, -322376401, 1687016542, 879870014, -1042723322
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -1964817676, -559875366, -178157308, -565287948, 315044791, 1926518347, -612419445, -185788152, -750432502, 1148501371, 139709216, 693420820, -2004650501, -1085414361, 444315414, 898338296
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u32m8 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m8 (int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1347612526, -2128496000, -2210419069, -1887341714, 2216017810, 291130117, 1723088259, 679955607, 416154432, 140415291, -1183469227, -3601345770, -2228044580, 810834094, 2612628734, -3172703091
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
