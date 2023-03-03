/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3890430345, 1359699992, 4173105240, 284113745, 4188431116, 3537685000, 691820570, 3115096174, 633242715, 1750681129, 2302062889, 2805132705, 3346416751, 1236395906, 2277825344, 2411265387
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1289059266, 1278579785, 664188831, 537785530, 2779636218, 4251431843, 596404574, 3769175591, 3041292285, 2421274513, 3800826064, 1830354442, 645031758, 2892385503, 2818468413, 3803034106
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    2992784034, 885779892, 680737947, 4129115624, 724594297, 1238314804, 1071841062, 1360823121, 1008504085, 4255050511, 79231468, 3037360774, 491856399, 2441590328, 362669639, 3746584694
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    5179489612, 2638279778, 4837294071, 821899276, 6968067335, 7789116844, 1288225144, 6884271766, 3674535000, 4171955643, 6102888954, 4635487147, 3991448509, 4128781410, 5096293758, 6214299493
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
