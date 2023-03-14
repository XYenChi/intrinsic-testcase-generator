/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    40, 248, 115, 153, 169, 12, 242, 43, 58, 246, 44, 219, 73, 25, 130, 167
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    194, 193, 129, 116, 24, 32, 157, 39, 8, 168, 145, 219, 75, 226, 209, 111
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16m4_t data1_v = __riscv_vle16_v_u16m4 (in1, vl);
    vuint16m4_t data2_v = __riscv_vle16_v_u16m4 (in2, vl);
    vuint16m4_t out_v = __riscv_vle16_v_u16m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i16m4 (data1_v, data2_v, vl);
        void __riscv_vse16_v_u16m4 (uint16_t *out, vuint16m4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    7760, 47864, 14835, 17748, 4056, 384, 37994, 1677, 464, 41328, 6380, 47961, 5475, 5650, 27170, 18537
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
