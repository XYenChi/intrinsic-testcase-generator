/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -59, -121, 105, 6, 60, -72, 80, -5, -75, -26, 98, -73, -108, 92, 4, 73
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -22, -31, -74, 113, 59, -19, -81, 10, -122, -61, -29, -20, -55, -88, -71, -90
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const int out_data[] = {
    78, 86, -74, 98, -80, -1, -5, -42, -104, 81, 50, 6, -125, -19, 123, -80
    };
    const int64_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4_m (mask, in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4_m (mask, in2, vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m4 (bool64_t mask, int64_t *out, vint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    18446744073709551535, 18446744073709551464, 18446744073709551542, 98, 119, 18446744073709551525, 18446744073709551611, 5, 18446744073709551512, 18446744073709551529, 50, 6, 18446744073709551491, 4, 18446744073709551549, 18446744073709551599
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
