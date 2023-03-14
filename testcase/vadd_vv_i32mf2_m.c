/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    91, 102, -112, 34, -64, 75, -53, -88, 44, 91, 116, 0, -125, 14, -34, 55
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -35, -47, 13, 16, -92, 53, -28, -13, -43, -103, 91, 82, 23, 78, 58, 2
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int out_data[] = {
    1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1
    };
    const int32_t *out = &out_data[0];
    uint64_t masked[] = {
    0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0
    };
    const uint64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32mf2 (bool32_t mask, int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1, 55, 4294967197, 1, 1, 1, 1, 4294967195, 1, 4294967284, 207, 82, 4294967194, 92, 24, 1
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
