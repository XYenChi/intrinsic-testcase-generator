/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -103, -79, 56, -59, -62, -28, -113, 15, -2, 100, -81, -103, -25, 48, 83, 30
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    79, 74, 49, -51, -121, -60, -31, -91, -111, -3, -88, 122, -53, 69, -84, -71
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i32m1 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m1 (int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    4294959159, 4294961450, 2744, 3009, 7502, 1680, 3503, 4294965931, 222, 4294966996, 7128, 4294954730, 1325, 3312, 4294960324, 4294965166
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
