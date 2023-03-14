/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    76, 85, 91, 69, 149, 204, 31, 14, 248, 170, 109, 218, 79, 248, 78, 169
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    81, 218, 42, 22, 187, 93, 159, 255, 84, 224, 59, 242, 233, 79, 60, 92
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m1(avl);
    const uint out_data[] = {
    0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1
    };
    const uint16_t *out = &out_data[0];
    uint16_t masked[] = {
    0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0
    };
    const uint16_t *mask = &masked[0];
    vuint16m1_t data1_v = __riscv_vle16_v_u16m1_m (mask, in1, vl);
    vuint16m1_t data2_v = __riscv_vle16_v_u16m1_m (mask, in2, vl);
    vuint16m1_t out_v = __riscv_vle16_v_u16m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16m1 (bool16_t mask, uint16_t *out, vuint16m1_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    0, 1, 133, 91, 336, 297, 0, 269, 1, 0, 168, 460, 0, 0, 1, 1
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
