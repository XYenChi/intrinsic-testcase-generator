/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -86, -23, -35, -19, -40, 118, 77, 116, 15, 116, -62, -78, 74, -92, -109, 104
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -60, 87, -119, 10, -103, -117, -63, -81, 106, 91, 94, 3, 86, -80, 31, -17
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    const int out_data[] = {
    0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0
    };
    const int16_t *out = &out_data[0];
    uint8_t masked[] = {
    1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0
    };
    const uint8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, in2, vl);
    vint16m2_t out_v = __riscv_vle16_v_i16m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_i16m2 (bool16_t mask, int16_t *out, vint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    65390, 0, 0, 65527, 1, 1, 1, 0, 121, 1, 32, 0, 160, 65364, 65458, 0
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
