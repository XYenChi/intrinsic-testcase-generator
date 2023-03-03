/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    130, 39, 174, 237, 143, 186, 57, 197, 109, 198, 115, 89, 169, 206, 19, 84
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    129, 12, 31, 177, 256, 221, 169, 136, 6, 68, 242, 237, 152, 149, 111, 165
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf2(size_t avl);
    const int out_data[] = {
    77, 18, 161, 145, 148, 204, 17, 95, 118, 164, 163, 47, 177, 172, 84, 2
    };
    const int8_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2_m (mask, *in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i8mf2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse8mf2_v_i8 (vbool8_t mask, int8mf2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    77, 39, 161, 145, 256, 204, 169, 197, 118, 198, 242, 237, 177, 172, 84, 165
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
