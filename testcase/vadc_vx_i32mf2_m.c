/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2553171909, 366362029, 3866875200, 1438901152, 980491566, 3900712635, 1029167597, 2328463491, 1901190538, 3956353854, 4056220153, 2962995715, 1938927322, 3782827315, 2873738163, 757609149
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    642429531, 212099039, 2644880020, 1152525597, 3423043984, 715598408, 3701678631, 2908095764, 1418683968, 120961420, 2136306939, 30104211, 2902331374, 2480055667, 2832303278, 130240694
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    660632173, 3612656642, 686563777, 941686840, 4031442645, 3965742350, 3275355285, 2235842863, 1137664298, 1774826335, 3091844977, 956360623, 3282513297, 1851904636, 2416353150, 1695571565
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3195601441, 578461068, 6511755220, 2591426750, 4403535551, 4616311044, 4730846229, 5236559255, 3319874506, 4077315275, 6192527093, 2993099926, 4841258696, 6262882983, 5706041442, 887849844
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
