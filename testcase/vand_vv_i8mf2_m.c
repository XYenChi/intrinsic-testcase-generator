/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    214, 198, 5, 87, 9, 201, 93, 133, 160, 106, 176, 38, 142, 105, 219, 112
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    163, 224, 252, 95, 218, 213, 210, 179, 244, 222, 250, 194, 95, 41, 71, 51
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf2(size_t avl);
    const int out_data[] = {
    155, 113, 10, 235, 239, 75, 124, 131, 15, 121, 129, 49, 106, 37, 203, 230
    };
    const int8_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2_m (mask, *in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16_t __riscv_vse8mf2_v_i8 (vbool8_t mask, int8mf2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    155, 224, 10, 95, 218, 75, 210, 179, 15, 121, 129, 194, 106, 37, 203, 230
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