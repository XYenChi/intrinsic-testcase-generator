/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    13, 186, 143, 136, 97, 215, 155, 3, 229, 152, 82, 131, 175, 200, 171, 40
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    145, 12, 167, 215, 39, 108, 68, 65, 5, 217, 30, 72, 84, 31, 89, 218
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    uint4_t masked[] = {
    1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1
    };
    const uint4_t *mask = &masked[0];
    vuint16m4_t data1_v = __riscv_vle16_v_u16m4 (in1, vl);
    vuint16m4_t data2_v = __riscv_vle16_v_u16m4 (in2, vl);
    vuint16m4_t out_v = __riscv_vle16_v_u16m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16m4 (uint16_t *out, vuint16m4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    159, 199, 311, 352, 137, 324, 223, 68, 235, 369, 112, 203, 259, 231, 260, 259
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
