/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    -73, -33, -108, 110, 109, 13, -50, -104, 42, -13, -126, -23, -86, -18, -48, 86
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -3, -16, -44, 29, 114, -58, -35, 115, -60, 34, -69, 53, 94, 116, 106, 13
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m4_t data1_v = __riscv_vle64_v_i64m4 (in1, vl);
    vint64m4_t data2_v = __riscv_vle64_v_i64m4 (in2, vl);
    vint64m4_t out_v = __riscv_vle64_v_i64m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vv_i64m4 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m4 (int64_t *out, vint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    18446744073709551398, 18446744073709551089, 18446744073709546864, 18446744073709548427, 18446744073709539190, 755, 18446744073709549867, 11961, 2521, 442, 18446744073709542922, 1220, 8085, 2088, 5088, 18446744073709550498
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
