/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3508732691, 2707878546, 4094808943, 3167086854, 1830417573, 115261685, 451368748, 1607927103, 772638686, 995588591, 1639422835, 3486631380, 508247705, 3594823898, 3326722211, 1010759445
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2482870278, 3073480321, 1637029343, 1055463304, 2357699702, 2585799057, 448350560, 3323824127, 1706924792, 1205077056, 4179553027, 3575068122, 3565735921, 1448125700, 1431976285, 852930029
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vx_i32m1 (data1_v, data2_v, mask, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    5991602969, 5781358867, 5731838286, 4222550158, 4188117275, 2701060742, 899719308, 4931751230, 2479563478, 2200665647, 5818975862, 7061699502, 4073983626, 5042949598, 4758698496, 1863689474
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
