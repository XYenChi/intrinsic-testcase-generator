/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4292178093, 3067737165, 303567189, 3032867920, 505338453, 3828041709, 3992116559, 181991817, 2646487251, 4075366690, 248920375, 636596367, 1864926678, 2794405122, 3784900618, 1991200029
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1733904124, 3145284314, 1001438367, 1651035161, 3541198443, 443307801, 924382350, 2330582402, 2025100526, 3053103394, 3985494497, 1929689007, 2378171280, 3609099062, 36835517, 1683721927
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, size_t vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1733904124, 3145284314, 1001438367, 1651035161, 3541198443, 443307801, 924382350, 2330582402, 2025100526, 3053103394, 3985494497, 1929689007, 2378171280, 3609099062, 36835517, 1683721927
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
