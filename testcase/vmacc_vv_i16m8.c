/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    17767, 31975, 38653, 21796, 1962, 45868, 20649, 34228, 55291, 53889, 3115, 28469, 33223, 35936, 882, 26701
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    2895, 10157, 9528, 3476, 24615, 38697, 2508, 26252, 5270, 24236, 44274, 44176, 38856, 49313, 21743, 31175
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8 (*in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8 (*in2, vl);
    vint16m8_t out_v = __riscv_vle16_v_i16m8 (*out, vl);
    const int out_data[] = {
    29164, 9110, 47703, 26740, 54344, 9083, 32094, 63953, 10016, 38409, 58267, 13628, 22419, 10613, 41905, 25098
    };
    const int16_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i16m8 (data1_v, data2_v, vl);
        void vint16m8_t __riscv_vse16_v_i16 (int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    51464629, 324779185, 368333487, 75789636, 48348974, 1774963079, 51819786, 898617409, 291393586, 1306092213, 137971777, 1257660172, 1290935307, 1772122581, 19219231, 832428773
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
