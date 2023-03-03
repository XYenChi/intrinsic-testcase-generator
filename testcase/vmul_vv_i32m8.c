/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1550367685, 3303244666, 1034595955, 4192659905, 4024087052, 2322086522, 3883286291, 1533649198, 3537624524, 2335777650, 3323973664, 3830137980, 663405050, 2260056279, 3385234262, 3554409405
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3823638617, 3319966321, 1546990381, 1066209318, 68927902, 3534840048, 1579702735, 2114469197, 1834843229, 3306427264, 2517519626, 3638042084, 4081996738, 2122467965, 564910652, 1717380798
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i32m8 (data1_v, data2_v, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    5928045750914891645, 10966661041142893786, 1600509990606508855, 4470253057915994790, 277371877959724904, 8208204432886633056, 6134437974680705885, 3242853988174754006, 6490986404605747996, 7723078904601849600, 8368168935427129664, 13934203158766750320, 2708017250072726900, 4796897051274602235, 1912354894119158824, 6104274460377605190
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
