/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    53, -120, -95, 72, 98, -19, -35, -91, -45, -84, 28, -116, 80, 50, -36, 37
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    46, -95, -95, 37, 46, -78, -72, 9, -2, -42, -78, -79, -60, -62, -37, -49
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int out_data[] = {
    1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0
    };
    const int32_t *out = &out_data[0];
    uint16_t masked[] = {
    1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1
    };
    const uint16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmadd_vx_i32m2_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m2 (bool32_t mask, int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    99, 4294967176, 4294967201, 109, 98, 4294967199, 4294967224, 4294967205, 4294967251, 4294967212, 4294967218, 4294967101, 80, 50, 4294967260, 4294967247
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
