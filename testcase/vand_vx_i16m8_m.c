/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    28305, 51767, 11940, 23349, 40867, 63468, 50609, 384, 14316, 34002, 55030, 51808, 51065, 2769, 5011, 9278
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    65486, 31612, 48204, 29292, 34147, 55685, 24523, 59786, 22648, 3968, 19194, 62991, 5924, 61577, 46503, 41497
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    58767, 36210, 16323, 51098, 19813, 60575, 9959, 47908, 7663, 64558, 14484, 43702, 35781, 64028, 9550, 55005
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    65486, 31612, 48204, 51098, 34147, 60575, 24523, 47908, 22648, 3968, 19194, 43702, 5924, 64028, 9550, 55005
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
