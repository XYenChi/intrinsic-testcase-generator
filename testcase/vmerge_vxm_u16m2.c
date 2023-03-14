/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    209, 145, 184, 57, 181, 162, 241, 45, 187, 209, 145, 97, 70, 116, 20, 31
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    206, 116, 106, 74, 225, 252, 139, 236, 209, 100, 99, 180, 131, 255, 116, 254
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    uint8_t masked[] = {
    0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1
    };
    const uint8_t *mask = &masked[0];
    vuint16m2_t data1_v = __riscv_vle16_v_u16m2 (in1, vl);
    vuint16m2_t data2_v = __riscv_vle16_v_u16m2 (in2, vl);
    vuint16m2_t out_v = __riscv_vle16_v_u16m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16m2 (uint16_t *out, vuint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    209, 145, 106, 57, 181, 252, 241, 45, 187, 209, 99, 97, 70, 116, 20, 254
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
