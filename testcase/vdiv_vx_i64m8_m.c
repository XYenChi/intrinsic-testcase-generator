/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    122, 10, 32, -57, 94, 57, -17, 119, -68, 84, 4, 28, 26, 91, -105, -100
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -64, 59, -60, 90, 10, 17, -69, 107, -88, 112, -124, 54, -3, -68, -117, 112
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const int out_data[] = {
    0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0
    };
    const int64_t *out = &out_data[0];
    uint8_t masked[] = {
    0, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1
    };
    const uint8_t *mask = &masked[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8_m (mask, in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8_m (mask, in2, vl);
    vint64m8_t out_v = __riscv_vle64_v_i64m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i64m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m8 (bool64_t mask, int64_t *out, vint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    0, 5, 18446744073709551614, 0, 0, 0, 4, 1, 1, 0, 18446744073709551585, 1, 18446744073709551615, 18446744073709551615, 1, 18446744073709551614
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
