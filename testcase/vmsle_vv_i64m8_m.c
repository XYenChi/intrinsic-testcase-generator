/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    31, 51, 126, -116, -64, 38, 127, -79, 81, 78, 106, 40, -17, -35, 20, -29
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    77, -99, -1, -118, -39, 56, -16, 103, 116, 126, 2, -109, -84, 27, -125, 115
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const int out_data[] = {
    0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0
    };
    const int64_t *out = &out_data[0];
    uint8_t masked[] = {
    1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0
    };
    const uint8_t *mask = &masked[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8_m (mask, in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8_m (mask, in2, vl);
    vint64m8_t out_v = __riscv_vle64_v_i64m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmsle_vv_64m8_b8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m8 (bool64_t mask, int64_t *out, vint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0
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
