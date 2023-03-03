/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    10883, 44004, 23773, 47893, 31701, 26477, 23137, 59074, 29766, 55817, 26816, 19145, 25420, 36822, 1129, 8487
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    11278, 51499, 21584, 22375, 11675, 50849, 24093, 6012, 58292, 2205, 26451, 32203, 36264, 5438, 32909, 54503
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1 (*in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1 (*in2, vl);
    vint16m1_t out_v = __riscv_vle16_v_i16m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i16m1 (data1_v, data2_v, vl);
        void vint16m1_t __riscv_vse16_v_i16 (int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    122738474, 2266161996, 513116432, 1071605875, 370109175, 1346328973, 557439741, 355152888, 1735119672, 123076485, 709310016, 616526435, 921830880, 200238036, 37154261, 462566961
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
