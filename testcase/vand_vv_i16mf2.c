/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    3762, 3663, 35373, 53728, 30746, 29958, 35225, 26900, 39503, 52047, 61655, 64744, 10685, 56109, 42694, 23819
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    26925, 9319, 59377, 31224, 11955, 61025, 23006, 27174, 45248, 25914, 26616, 49213, 24149, 65387, 14249, 14233
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2 (*in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2 (*in2, size_t vl);
    vint16mf2_t out_v = __riscv_vle16_v_i16mf2 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16mf2_t __riscv_vse16_v_i16 (int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    26925, 9319, 59377, 31224, 11955, 61025, 23006, 27174, 45248, 25914, 26616, 49213, 24149, 65387, 14249, 14233
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
