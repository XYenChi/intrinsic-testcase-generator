/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    194, 198, 229, 191, 75, 143, 168, 109, 27, 212, 176, 194, 22, 231, 114, 37
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    9, 102, 78, 104, 119, 178, 64, 5, 15, 85, 136, 210, 25, 216, 124, 253
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16m2_t data1_v = __riscv_vle16_v_u16m2 (in1, vl);
    vuint16m2_t data2_v = __riscv_vle16_v_u16m2 (in2, vl);
    vuint16m2_t out_v = __riscv_vle16_v_u16m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmsne_vx_16m2_b8 (data1_v, data2_v, vl);
        void __riscv_vse16_v_u16m2 (uint16_t *out, vuint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
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
