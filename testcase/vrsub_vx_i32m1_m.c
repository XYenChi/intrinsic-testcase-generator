/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -94, 77, -51, 83, -22, -103, 4, 57, 39, 69, 6, 29, 62, -35, -128, 8
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    42, -3, -13, -62, 45, -97, 79, -10, -18, -93, -35, 61, 67, -27, -77, 21
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int out_data[] = {
    0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1
    };
    const int32_t *out = &out_data[0];
    uint32_t masked[] = {
    0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0
    };
    const uint32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrsub_vx_i32m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m1 (bool32_t mask, int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    0, 4294967216, 0, 4294967151, 67, 1, 75, 4294967229, 0, 4294967134, 0, 32, 5, 0, 0, 1
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
