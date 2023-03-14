/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -58, -35, -111, -118, -26, 101, -58, -15, 31, 21, -28, 123, -73, 72, -22, -30
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    53, 38, -17, -93, -105, 84, -64, 96, 8, 13, 2, 56, 13, 68, 111, 107
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int out_data[] = {
    1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0
    };
    const int32_t *out = &out_data[0];
    uint8_t masked[] = {
    0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1
    };
    const uint8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m4 (bool32_t mask, int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1, 0, 4294967168, 1, 4294967165, 185, 1, 81, 39, 1, 1, 179, 1, 1, 0, 77
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
