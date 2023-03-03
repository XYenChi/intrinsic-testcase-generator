/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    43077, 28480, 41929, 34779, 32457, 30040, 11542, 7829, 44054, 64857, 18753, 64928, 50296, 15664, 46185, 10912
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    24254, 64626, 54157, 47080, 28845, 16723, 22892, 10399, 4248, 10730, 11023, 33378, 16585, 47273, 1834, 63535
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
    24254, 64626, 54157, 47080, 28845, 16723, 22892, 10399, 4248, 10730, 11023, 33378, 16585, 47273, 1834, 63535
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
