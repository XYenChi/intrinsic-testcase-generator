/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2738459435, 2935853491, 812152801, 1011739337, 1415736910, 2603678398, 1385842852, 2116598955, 98044609, 1323620710, 3603630923, 182487009, 1035802741, 3445883562, 2865871565, 4287749430
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3946711906, 1713611807, 2330104419, 277515415, 709426058, 246387308, 3506255236, 437653427, 3447800204, 3145447927, 2744594447, 1133367728, 1227523805, 2974317226, 998227459, 3546452027
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    3842236894, 1983736504, 2259291490, 2165693034, 1305557691, 629016323, 837616754, 3017840579, 3607808962, 3611194178, 727659342, 891932043, 3256140160, 356672833, 3331170638, 178620371
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3842236894, 1983736504, 2259291490, 1011739337, 1415736910, 629016323, 837616754, 3017840579, 3607808962, 3145447927, 727659342, 1133367728, 1227523805, 3445883562, 3331170638, 4287749430
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
