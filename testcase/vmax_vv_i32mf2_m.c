/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2269997406, 3682320535, 2514112923, 1921074835, 3422733718, 4187296848, 2054309926, 1277157921, 2941942420, 1502259638, 495318687, 376702861, 3514977879, 379049988, 3233265955, 1193174634
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2455702147, 934130976, 3662033434, 870085445, 3980301231, 4095676040, 605566685, 1631891201, 2314225697, 12245962, 2520857870, 1430514724, 622528316, 1472776438, 4252968577, 4029347099
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    3790192370, 3677546053, 4181985027, 2451508980, 846284910, 3841972734, 2576730926, 192365989, 1094092140, 3156195389, 4182510567, 2866451855, 2306644559, 4275179755, 3260658684, 2923355212
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    2455702147, 3682320535, 4181985027, 2451508980, 3980301231, 4187296848, 2576730926, 1631891201, 1094092140, 3156195389, 4182510567, 2866451855, 3514977879, 1472776438, 4252968577, 4029347099
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
