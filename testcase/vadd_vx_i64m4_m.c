/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    242, 171, 8, 128, 138, 155, 121, 122, 181, 15, 129, 223, 78, 242, 200, 201
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    186, 69, 47, 221, 200, 143, 90, 6, 253, 228, 240, 146, 134, 93, 147, 35
    };
    const int64_t *in2 = &data2[0];
    const int out_data[] = {
    24, 201, 83, 211, 133, 150, 246, 26, 107, 240, 234, 26, 126, 115, 206, 177
    };
    int64_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 0
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint64m4_t out_data = __riscv_vadd_vx_i64m4_m (mask, data1, data2, vl)
        vint64m4_t __riscv_vse64_v_i64m4 (out, out_data, vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    428, 240, 55, 349, 338, 298, 246, 128, 434, 240, 369, 26, 212, 335, 206, 177
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
