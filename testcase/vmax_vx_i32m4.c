/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2499942632, 896716365, 2808033294, 2307740321, 1494014661, 1067376811, 495729464, 839892430, 2434576611, 1764334805, 2540757127, 2226949872, 2440153922, 1202226175, 500461819, 1233907768
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    712857823, 3615851829, 452857505, 4250228444, 2065821214, 4151544676, 2427017388, 467377660, 360421507, 2434677502, 404389929, 504398493, 2307873059, 247786214, 3290047118, 1499889644
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i32m4 (data1_v, data2_v, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    2499942632, 3615851829, 2808033294, 4250228444, 2065821214, 4151544676, 2427017388, 839892430, 2434576611, 2434677502, 2540757127, 2226949872, 2440153922, 1202226175, 3290047118, 1499889644
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
