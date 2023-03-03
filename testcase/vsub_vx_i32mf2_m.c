/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3313877651, 1909966621, 1180112248, 3702535722, 3886721168, 1717237546, 3865739484, 2432152197, 3797852709, 109734337, 1609961048, 507261726, 2075142017, 2764945901, 387903272, 2171219492
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    273544676, 125421031, 1903800035, 883645045, 227842861, 109288641, 3913930697, 3691009567, 908372611, 252513312, 3898889641, 2088016239, 314799735, 3657449202, 1159183659, 105319744
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    1407265357, 1858643192, 232377392, 3275337002, 3549033502, 3586367854, 270657369, 3042422355, 1497987051, 1793816661, 834561524, 513707093, 1908698264, 456411452, 4026825550, 1577137302
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1407265357, 1784545590, 232377392, 2818890677, 3658878307, 3586367854, -48191213, -1258857370, 2889480098, 1793816661, -2288928593, 513707093, 1760342282, 456411452, -771280387, 1577137302
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
