/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    375, 65257, 60971, 58018, 53008, 36738, 47509, 48606, 56374, 44447, 48580, 51617, 28661, 62718, 25493, 21376
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    64152, 17367, 18459, 62579, 22866, 38482, 60239, 29147, 60273, 26594, 14518, 29164, 54834, 49644, 23368, 49029
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1 (*in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1 (*in2, vl);
    vint16m1_t out_v = __riscv_vle16_v_i16m1 (*out, vl);
    const int out_data[] = {
    50612, 47787, 49443, 31124, 36934, 27605, 17437, 49346, 3389, 41889, 12210, 28499, 10948, 63159, 22725, 29924
    };
    const int16_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i16m1 (data1_v, data2_v, vl);
        void vint16m1_t __riscv_vse16_v_i16 (int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    24107612, 1133366106, 1125513132, 3630739546, 1212117862, 1413779321, 2861912088, 1416768428, 3397833491, 1182065407, 705296650, 1505386687, 1571608222, 3113635551, 595743149, 1048073828
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
