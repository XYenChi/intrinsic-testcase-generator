/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -123, -71, -107, 111, -23, -111, -20, 75, 106, 35, -71, -8, 19, 66, -63, 73
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    86, 23, 15, 25, 67, 13, -12, -118, -38, 21, -118, 46, -51, -9, 105, -105
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i32m8 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m8 (int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    4294956718, 4294965663, 4294965691, 2775, 4294965755, 4294965853, 240, 4294958446, 4294963268, 735, 8378, 4294966928, 4294966327, 4294966702, 4294960681, 4294959631
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