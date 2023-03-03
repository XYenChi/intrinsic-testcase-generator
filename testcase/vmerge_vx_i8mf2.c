/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    46, 108, 105, 226, 162, 10, 148, 104, 101, 109, 228, 250, 22, 136, 246, 177
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    227, 57, 20, 9, 249, 74, 56, 62, 179, 217, 249, 22, 152, 96, 244, 245
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf2(size_t avl);
    bool16_t masked[] = {
    0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2 (mask, *in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vx_i8mf2 (data1_v, data2_v, size_t vl);
        void vint16_t __riscv_vse8mf2_v_i8 (vbool8_t mask, int8mf2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    46, 108, 20, 9, 162, 74, 56, 104, 101, 109, 249, 22, 152, 136, 244, 245
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
