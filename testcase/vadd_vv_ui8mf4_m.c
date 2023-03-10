/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    224, 84, 34, 174, 133, 4, 211, 121, 246, 12, 21, 55, 95, 247, 23, 204
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    176, 219, 128, 33, 82, 80, 174, 144, 190, 74, 60, 233, 95, 9, 146, 132
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf4(avl);
    const int out_data[] = {
    17, 74, 238, 144, 79, 64, 241, 138, 207, 56, 105, 239, 192, 8, 242, 34
    };
    const int8_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4_m (mask, in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4_m (mask, in2, vl);
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_i8mf4 (bool8_t mask, int8_t *out, vint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    17, 255, 162, 144, 79, 64, 255, 255, 255, 86, 105, 255, 190, 8, 242, 34
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
