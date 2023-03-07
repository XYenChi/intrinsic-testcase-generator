/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -112, 83, -34, 120, 125, -72, 41, -10, 111, -64, -114, 123, 11, 86, -72, -126
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    -20, 55, 75, -120, 106, 109, -85, 45, -85, 119, 115, -109, 71, 42, -110, -18
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m8(avl);
    const int out_data[] = {
    -51, 11, 102, 63, -112, 17, 68, 91, 84, -81, 67, -16, 35, -93, -95, -76
    };
    const int8_t *out = &out_data[0];
    bool1_t masked[] = {
    1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0
    };
    const bool1_t *mask = &masked[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8_m (mask, *in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8_m (mask, *in2, vl);
    vint8m8_t data1_v = __riscv_vle8_v_i8m8_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_u8m8_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_i8m8 (bool8_t mask, int8_t *out, vint8m8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -50, 11, 102, 64, -111, 17, 69, 92, 84, -81, 67, -15, 36, -92, -94, -76
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
