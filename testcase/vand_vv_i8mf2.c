/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    20, 184, 56, 242, 161, 165, 39, 156, 30, 98, 49, 12, 176, 233, 176, 187
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    22, 119, 81, 203, 48, 79, 189, 91, 49, 172, 113, 228, 113, 52, 44, 217
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf2(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2 (*in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2 (*in2, size_t vl);
    vint8mf2_t out_v = __riscv_vle8_v_i8mf2 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint8mf2_t __riscv_vse8_v_i8 (int8mf2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    22, 119, 81, 203, 48, 79, 189, 91, 49, 172, 113, 228, 113, 52, 44, 217
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
