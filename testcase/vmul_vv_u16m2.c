/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    139, 244, 78, 92, 101, 130, 244, 167, 186, 224, 23, 246, 102, 218, 229, 164
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    187, 95, 206, 57, 93, 231, 103, 99, 185, 105, 198, 202, 23, 97, 31, 112
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16m2_t data1_v = __riscv_vle16_v_u16m2 (in1, vl);
    vuint16m2_t data2_v = __riscv_vle16_v_u16m2 (in2, vl);
    vuint16m2_t out_v = __riscv_vle16_v_u16m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i16m2 (data1_v, data2_v, vl);
        void __riscv_vse16_v_u16m2 (uint16_t *out, vuint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    25993, 23180, 16068, 5244, 9393, 30030, 25132, 16533, 34410, 23520, 4554, 49692, 2346, 21146, 7099, 18368
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
