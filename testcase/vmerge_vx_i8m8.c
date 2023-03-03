/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    204, 109, 0, 82, 44, 25, 167, 187, 185, 166, 95, 135, 246, 186, 66, 222
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    193, 71, 159, 253, 173, 63, 30, 246, 238, 79, 210, 156, 36, 158, 23, 195
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m8(size_t avl);
    bool1_t masked[] = {
    1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0
    };
    const bool1_t *mask = &masked[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8 (mask, *in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vx_i8m8 (data1_v, data2_v, size_t vl);
        void vint1_t __riscv_vse8m8_v_i8 (vbool8_t mask, int8m8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    193, 109, 0, 253, 173, 63, 167, 246, 238, 166, 210, 156, 36, 158, 66, 222
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
