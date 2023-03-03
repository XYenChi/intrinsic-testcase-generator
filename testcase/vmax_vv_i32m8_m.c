/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1201577411, 3313805295, 2077475453, 1049289611, 2063043283, 484900049, 2183483987, 315441503, 1100253331, 3790850045, 2708021873, 3068754192, 967005095, 3582895469, 3487317062, 1116785517
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3735800530, 2946808856, 1795470144, 3278977628, 2146947007, 3446942843, 676786539, 717837960, 2453511477, 2401928071, 1980339872, 3357203899, 1413391569, 431765573, 3668642563, 92819173
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    3063421316, 1400970718, 2012062541, 1657894489, 2391824491, 1311874915, 1185016611, 2598812682, 1008481938, 562885335, 1637703242, 3585890958, 3934406325, 2713088445, 1008780242, 2783649068
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3063421316, 3313805295, 2012062541, 1657894489, 2391824491, 1311874915, 1185016611, 717837960, 1008481938, 562885335, 1637703242, 3357203899, 1413391569, 2713088445, 1008780242, 2783649068
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
