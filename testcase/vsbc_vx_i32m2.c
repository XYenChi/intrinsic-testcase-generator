/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1240059830, 631146122, 1164707498, 1931161090, 1712469411, 3430155679, 2581290597, 1960522450, 3487686264, 2405176150, 2509501981, 2478030073, 1742783686, 3983569805, 463181026, 1332965090
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3079342248, 1871144117, 1438483627, 374536009, 2813233176, 593647204, 1819038728, 4013898792, 2786848715, 3984590913, 2969327659, 1880777496, 2721683026, 4273837253, 158601844, 3936923937
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vx_i32m2 (data1_v, data2_v, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    -1839282418, -1239997995, -273776129, 1556625081, -1100763765, 2836508475, 762251869, -2053376342, 700837549, -1579414763, -459825678, 597252577, -978899340, -290267448, 304579182, -2603958847
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
