/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -104, -68, -67, 55, 75, 114, 90, -24, -28, 110, -5, 73, -21, 113, -43, 80
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    8, 19, -18, -81, 75, -61, -108, -70, 116, 2, 115, -106, 37, -22, -56, 78
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i32m2 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m2 (int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    4294966464, 4294966004, 1206, 4294962841, 5625, 4294960342, 4294957576, 1680, 4294964048, 220, 4294966721, 4294959558, 4294966519, 4294964810, 2408, 6240
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
