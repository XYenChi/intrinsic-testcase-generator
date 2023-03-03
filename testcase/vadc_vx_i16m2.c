/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    62764, 57522, 19592, 3308, 50140, 57392, 12163, 12661, 26704, 47502, 51018, 2315, 28156, 22835, 11769, 19294
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    15458, 21682, 19408, 63314, 6006, 9836, 36852, 39362, 27417, 39111, 17963, 19519, 65409, 34017, 27712, 54651
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2 (*in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2 (*in2, vl);
    vint16m2_t out_v = __riscv_vle16_v_i16m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vx_i16m2 (data1_v, data2_v, mask, vl);
        void vint16m2_t __riscv_vse16_v_i16 (int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    78222, 79204, 39000, 66622, 56146, 67228, 49015, 52023, 54121, 86613, 68981, 21834, 93565, 56852, 39481, 73945
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
