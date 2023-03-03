/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2730229285, 2292929418, 1697599490, 3903735735, 419091707, 1426279684, 954103245, 1654541547, 2385854166, 42750105, 4077905464, 2011259158, 1832565010, 2802229653, 790100962, 3193505676
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2177440965, 2072597102, 494547115, 3057507771, 1689708260, 1221767365, 62737718, 3848844801, 2169977361, 797991400, 2853163144, 2228944674, 4000619849, 1302118705, 844332973, 4045759870
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    2902195260, 3628450061, 221793733, 2404509536, 1025637080, 2985894750, 2011731706, 2436191646, 3847459024, 3418633213, 2339019688, 1551122300, 709788551, 3484069899, 894923464, 3892260216
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    7923658489640189101, 8319779886610794499, 376516928025996170, 9386569800831468961, 429835994619695561, 4258721020487259000, 1919399748763985970, 4030780294761316362, 9179476140924693985, 146146928812237365, 9538301166098775233, 3119708931053023401, 1300733663061200510, 9763163984102515048, 707079889822772368, 12429955092264986017
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
