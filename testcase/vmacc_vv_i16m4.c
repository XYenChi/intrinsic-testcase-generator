/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    53977, 1251, 46118, 13130, 53618, 17639, 14824, 2907, 52398, 57440, 65319, 14704, 23164, 22294, 55743, 62731
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    29440, 5058, 58267, 54260, 31485, 4578, 51242, 23158, 4230, 12465, 44606, 25620, 23672, 43447, 5017, 13514
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4 (*in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4 (*in2, vl);
    vint16m4_t out_v = __riscv_vle16_v_i16m4 (*out, vl);
    const int out_data[] = {
    58804, 22259, 14554, 52411, 61504, 42819, 61233, 5524, 33829, 46141, 21349, 42884, 38043, 30696, 41645, 8510
    };
    const int16_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i16m4 (data1_v, data2_v, vl);
        void vint16m4_t __riscv_vse16_v_i16 (int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    1589141684, 6349817, 2687172060, 712486211, 1688224234, 80794161, 759672641, 67325830, 221677369, 716035741, 2913640663, 376759364, 548376251, 968638114, 279704276, 847755244
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
