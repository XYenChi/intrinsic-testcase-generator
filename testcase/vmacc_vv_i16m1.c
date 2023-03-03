/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    8685, 40456, 64337, 11684, 3160, 47097, 32060, 29201, 36911, 21908, 22311, 65432, 12357, 34963, 56775, 63386
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    15720, 3953, 40688, 38682, 529, 5247, 7384, 48047, 17336, 62208, 42219, 53615, 53141, 5374, 31062, 59516
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
    20214, 35524, 8044, 8689, 10570, 17763, 59534, 41437, 44277, 46442, 54406, 21021, 29193, 19523, 38801, 50810
    };
    const int16_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i16m1 (data1_v, data2_v, vl);
        void vint16m1_t __riscv_vse16_v_i16 (int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    136548414, 159958092, 2617751900, 451969177, 1682210, 247135722, 236790574, 1403061884, 639933373, 1362899306, 942002515, 3508157701, 656692530, 187910685, 1763583851, 3772531986
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
