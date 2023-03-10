/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -107, -64, -15, 16, 32, 36, 35, -5, -62, -72, -78, -48, -92, -57, -3, -46
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -87, 35, -65, 37, -59, 13, -118, -18, -36, 12, 74, -65, 2, -57, -84, -47
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const int out_data[] = {
    73, 113, -122, -32, 83, -127, -61, 36, 21, -76, -73, -60, 67, -4, -52, 39
    };
    const int64_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8_m (mask, in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8_m (mask, in2, vl);
    vint64m8_t out_v = __riscv_vle64_v_i64m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m8 (bool64_t mask, int64_t *out, vint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    73, 113, 18446744073709551494, 18446744073709551584, 18446744073709551589, 49, 18446744073709551555, 36, 21, 18446744073709551540, 18446744073709551612, 18446744073709551503, 67, 18446744073709551502, 18446744073709551529, 18446744073709551523
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
