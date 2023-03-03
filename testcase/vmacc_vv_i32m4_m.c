/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2592255937, 2729900262, 2387234117, 3954103433, 2615382984, 2087482720, 2943439839, 2116965116, 2004849328, 3523168358, 3251640697, 2758550127, 3492744952, 127110951, 948700909, 2075720830
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1459070864, 4012342088, 3216587273, 1240718314, 1481755449, 363955297, 3524868323, 2337727393, 4198547225, 3001395728, 1367768149, 3139345183, 2101815655, 832770112, 1639371464, 168199017
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    3418531982, 1279804920, 2081959470, 2652533282, 4109650302, 3127247664, 928917805, 2595695551, 769994922, 39547347, 2785344401, 3518535315, 2127176868, 992332327, 3879991146, 1216578245
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    8861709826163877134, 3493739786416889040, 4970124676995237991, 10488390956502957107, 10748309470041261169, 6528075459760366080, 2734213674393433395, 5494996933223398916, 1543723801935112417, 139331961593246226, 9056939209452687498, 9706056040047235005, 7429686267718170336, 126136305793012978, 3680951127122151714, 2525276804471343350
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
