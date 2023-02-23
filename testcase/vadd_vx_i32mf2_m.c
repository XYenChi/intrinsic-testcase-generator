/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    100, 14, 31, 41, 28, 196, 211, 106, 100, 8, 243, 252, 55, 192, 148, 95
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    48, 166, 142, 249, 209, 69, 191, 102, 116, 234, 205, 81, 83, 177, 178, 113
    };
    const int32_t *in2 = &data2[0];
    const int out_data[] = {
    207, 134, 58, 70, 207, 45, 126, 211, 124, 148, 251, 201, 240, 108, 77, 117
    };
    int32_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1
    };
    const int *mask = &masked[0];
    for (size_t n = 0; n < vl; n++) {
        vint32mf2_t out_data = __riscv_vadd_vx_i32mf2_m (mask, data1, data2, vl)
        vint32mf2_t __riscv_vse32_v_i32mf2 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    148, 134, 58, 290, 237, 265, 126, 211, 216, 242, 448, 201, 138, 108, 326, 208
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
