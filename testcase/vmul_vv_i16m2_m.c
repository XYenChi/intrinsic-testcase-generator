/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    6813, 15770, 12597, 13722, 58760, 15242, 14039, 28395, 42603, 59036, 45820, 14193, 22700, 23798, 27619, 29021
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    23094, 32738, 34527, 25674, 14824, 27708, 19640, 52356, 21929, 14238, 44058, 36160, 28874, 53628, 44617, 43735
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    683, 30902, 56063, 28014, 31298, 42975, 24539, 64386, 33678, 54946, 51587, 13985, 59617, 324, 43588, 22350
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    157339422, 516278260, 434936619, 352298628, 31298, 42975, 24539, 1486648620, 934241187, 54946, 2018737560, 513218880, 59617, 1276239144, 43588, 22350
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
