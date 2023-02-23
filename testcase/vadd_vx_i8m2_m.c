/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    143, 5, 248, 200, 66, 61, 20, 76, 55, 63, 75, 168, 119, 233, 216, 19
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    42, 87, 40, 189, 172, 221, 216, 228, 10, 134, 123, 105, 112, 123, 39, 123
    };
    const int8_t *in2 = &data2[0];
    const int out_data[] = {
    67, 128, 156, 133, 173, 174, 245, 81, 1, 80, 65, 219, 93, 231, 7, 232
    };
    int8_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint8m2_t out_data = __riscv_vadd_vx_i8m2_m (mask, data1, data2, vl)
        vint8m2_t __riscv_vse8_v_i8m2 (out, out_data, vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    185, 92, 156, 389, 238, 174, 236, 81, 1, 197, 198, 219, 231, 231, 7, 142
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
