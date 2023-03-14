/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    85, -87, 65, 111, 109, -13, -29, -40, 5, -120, 12, 75, -51, 58, -108, -117
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    37, -14, -74, -39, -19, 82, -44, 96, 39, 108, -28, -14, -8, 112, 79, -5
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int out_data[] = {
    1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1
    };
    const int32_t *out = &out_data[0];
    uint32_t masked[] = {
    0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1
    };
    const uint32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i32m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m1 (bool32_t mask, int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1, 1, 4294962486, 0, 0, 4294966230, 1276, 0, 195, 4294954336, 1, 4294966246, 408, 0, 4294958764, 585
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
