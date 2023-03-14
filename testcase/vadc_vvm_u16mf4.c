/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    208, 10, 192, 29, 39, 216, 115, 99, 249, 81, 233, 218, 193, 111, 250, 141
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    209, 42, 156, 204, 34, 119, 70, 41, 154, 251, 123, 248, 41, 200, 242, 225
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    uint64_t masked[] = {
    0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0
    };
    const uint64_t *mask = &masked[0];
    vuint16mf4_t data1_v = __riscv_vle16_v_u16mf4 (in1, vl);
    vuint16mf4_t data2_v = __riscv_vle16_v_u16mf4 (in2, vl);
    vuint16mf4_t out_v = __riscv_vle16_v_u16mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16mf4 (uint16_t *out, vuint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    417, 52, 349, 234, 74, 336, 186, 140, 404, 333, 356, 466, 235, 312, 493, 366
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
