/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    102, 25, 1, 212, 83, 128, 200, 81, 135, 252, 164, 60, 46, 108, 133, 46
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    53, 9, 66, 104, 241, 242, 45, 243, 162, 40, 53, 161, 157, 64, 54, 147
    };
    const int64_t *in2 = &data2[0];
    const int out_data[] = {
    243, 113, 244, 118, 117, 103, 90, 134, 73, 139, 241, 92, 44, 7, 49, 13
    };
    int64_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint64m1_t out_data = __riscv_vadd_vx_i64m1_m (mask, data1, data2, vl)
        vint64m1_t __riscv_vse64_v_i64m1 (out, out_data, vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    155, 113, 67, 118, 117, 103, 245, 324, 297, 292, 217, 221, 203, 172, 187, 13
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
