/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -106, -11, 88, -114, 7, 10, 10, 98, 60, -36, 70, -76, 79, -71, -112, 73
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -124, 92, 112, 111, -101, -78, -110, 117, -67, 59, 59, 36, -40, -36, -97, -5
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (in1, vl);
    vuint32m2_t data2_v = __riscv_vle32_v_i32m2 (in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vwmul_vv_i32m2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m2 (int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    13144, 4294966284, 9856, 4294954642, 4294966589, 4294966516, 4294966196, 11466, 4294963276, 4294965172, 4130, 4294964560, 4294964136, 2556, 10864, 4294966931
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
