/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    32484, 54328, 27150, 38043, 9901, 17789, 55793, 4800, 32393, 14401, 57336, 8871, 47797, 54258, 12199, 2295
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    34454, 49596, 38894, 60514, 38177, 38400, 60472, 50371, 31326, 39437, 59503, 48553, 26280, 7636, 54921, 46766
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2 (*in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2 (*in2, vl);
    vint16m2_t out_v = __riscv_vle16_v_i16m2 (*out, vl);
    const int out_data[] = {
    42788, 30205, 60604, 10723, 13818, 38683, 38296, 41301, 28399, 47457, 54498, 38823, 27560, 26692, 38483, 39582
    };
    const int16_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i16m2 (data1_v, data2_v, vl);
        void vint16m2_t __riscv_vse16_v_i16 (int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    1119246524, 2694481693, 1056032704, 2302144825, 378004295, 683136283, 3373952592, 241822101, 1014771517, 567979694, 3411718506, 430752486, 1256132720, 414340780, 670019762, 107367552
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
