/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    33, -99, 40, -66, -107, 5, 115, 87, 117, -43, -46, 21, -126, 12, -82, 54
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -5, -9, -120, -92, -90, 121, 82, -102, 88, 6, 121, 81, 58, -87, -85, 75
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int out_data[] = {
    0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1
    };
    const int32_t *out = &out_data[0];
    uint4_t masked[] = {
    1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0
    };
    const uint4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i32m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m8 (bool32_t mask, int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    33, 4294967287, 40, 1, 1, 1, 1, 1, 117, 0, 1, 0, 0, 12, 4294967214, 1
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
