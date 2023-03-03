/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    129, 95, 32, 107, 178, 74, 180, 248, 99, 131, 148, 45, 153, 115, 6, 256
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    189, 52, 208, 184, 105, 159, 67, 30, 0, 247, 184, 39, 99, 74, 160, 157
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf2(size_t avl);
    const int out_data[] = {
    210, 64, 25, 33, 126, 24, 171, 165, 197, 192, 205, 158, 153, 194, 188, 88
    };
    const int8_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2_m (mask, *in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u8mf2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse8mf2_v_i8 (vbool8_t mask, int8mf2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    210, 43, 25, -77, 126, -85, 113, 218, 99, 192, -36, 158, 153, 41, 188, 88
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
