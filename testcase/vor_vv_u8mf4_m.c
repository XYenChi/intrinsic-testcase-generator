/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    3, 110, 206, 188, 219, 66, 117, 162, 221, 40, 148, 175, 99, 208, 224, 8
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    248, 85, 31, 42, 186, 30, 76, 93, 108, 39, 7, 245, 88, 86, 132, 21
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf4(avl);
    const uint out_data[] = {
    0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 1, 1
    };
    const uint8_t *out = &out_data[0];
    uint32_t masked[] = {
    1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0
    };
    const uint32_t *mask = &masked[0];
    vuint8mf4_t data1_v = __riscv_vle8_v_u8mf4_m (mask, in1, vl);
    vuint8mf4_t data2_v = __riscv_vle8_v_u8mf4_m (mask, in2, vl);
    vuint8mf4_t out_v = __riscv_vle8_v_u8mf4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vor_wv_8mf4u_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_u8mf4 (bool8_t mask, uint8_t *out, vuint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    251, 0, 1, 190, 1, 94, 125, 1, 253, 47, 1, 255, 0, 1, 1, 1
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
