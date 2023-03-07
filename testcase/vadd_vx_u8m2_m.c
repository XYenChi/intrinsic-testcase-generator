/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    29, -26, 126, -2, -49, -97, 46, -23, -103, -77, -111, -28, 27, -101, -17, -47
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    8, 54, -92, -66, 82, -77, 72, 121, -76, 24, 88, -123, -85, -85, -118, 31
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m2(avl);
    const int out_data[] = {
    53, 36, 10, 48, -63, -120, 66, 89, 81, 15, -2, 119, -120, -2, -99, -25
    };
    const int8_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vint8m2_t data1_v = __riscv_vle8_v_i8m2_m (mask, *in1, vl);
    vint8m2_t data2_v = __riscv_vle8_v_i8m2_m (mask, *in2, vl);
    vint8m2_t data1_v = __riscv_vle8_v_i8m2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u8m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m2 (bool8_t mask, int8_t *out, vint8m2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    54, 37, 10, 48, -63, -119, 66, 90, 81, 15, -2, 119, -120, -1, -99, -24
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
