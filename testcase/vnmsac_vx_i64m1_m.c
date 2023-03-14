/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    74, -23, 15, 65, 126, 37, 63, 15, 45, 66, -25, -6, 18, 120, -31, 76
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -90, -81, -46, 7, -62, -67, 77, -90, 56, -62, -19, 89, -117, 90, 95, -46
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const int out_data[] = {
    1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1
    };
    const int64_t *out = &out_data[0];
    uint64_t masked[] = {
    1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0
    };
    const uint64_t *mask = &masked[0];
    vint64m1_t data1_v = __riscv_vle64_v_i64m1_m (mask, in1, vl);
    vint64m1_t data2_v = __riscv_vle64_v_i64m1_m (mask, in2, vl);
    vint64m1_t out_v = __riscv_vle64_v_i64m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vx_i64m1_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m1 (bool64_t mask, int64_t *out, vint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    6661, 18446744073709549754, 691, 0, 1, 1, 18446744073709546766, 0, 1, 4092, 18446744073709551141, 0, 2106, 18446744073709540816, 0, 1
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
