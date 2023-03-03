/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    27807, 51753, 57335, 17342, 25915, 9571, 43578, 405, 56484, 50169, 26497, 48756, 46323, 16827, 50233, 22996
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    49954, 8886, 30962, 53343, 3868, 50487, 55016, 14524, 23374, 48082, 13210, 52933, 61763, 1556, 38324, 46882
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    8533, 25580, 2461, 14292, 57271, 60577, 60046, 60178, 63836, 63274, 34190, 16257, 44330, 57844, 4692, 47786
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    49954, 8886, 2461, 14292, 3868, 60577, 60046, 60178, 23374, 63274, 13210, 16257, 61763, 1556, 4692, 47786
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
