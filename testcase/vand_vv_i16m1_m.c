/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    27589, 37504, 29134, 59951, 29943, 11977, 8688, 31619, 43500, 60494, 65463, 26591, 57936, 23734, 9210, 42888
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    58974, 12426, 41789, 36472, 25420, 31057, 46429, 3986, 60073, 37451, 42112, 18788, 44388, 32447, 45870, 205
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    280, 22509, 41508, 1116, 4079, 5373, 29938, 51337, 12350, 35347, 59720, 41442, 5129, 3348, 6653, 1344
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    58974, 12426, 41508, 1116, 25420, 31057, 29938, 51337, 12350, 35347, 59720, 41442, 44388, 3348, 45870, 205
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
