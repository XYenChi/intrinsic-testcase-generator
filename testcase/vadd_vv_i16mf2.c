/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    30808, -16291, -6676, -18451, 23277, 3130, 9488, -10894, -8094, 19097, 23999, 17088, 6126, 3414, 9850, -29675
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -10948, 3349, -1391, -2252, -3871, -28318, -16274, -15259, 17510, -7796, -6493, 1278, 15473, 20286, -2157, -24010
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2 (*in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2 (*in2, vl);
    vint16mf2_t out_v = __riscv_vle16_v_i16mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i16mf2 (data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf2 (int16_t *out, vint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    52076, -37462, 12156, -31935, 52020, -936, 38023, -16133, 22719, 17691, 26370, -8971, -20479, 12996, -12511, -57940
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
