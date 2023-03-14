/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    173, 59, 219, 179, 55, 194, 148, 179, 189, 211, 174, 67, 115, 224, 240, 207
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    187, 17, 126, 147, 199, 209, 155, 154, 146, 160, 158, 63, 214, 82, 99, 12
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m1(avl);
    const uint out_data[] = {
    1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0
    };
    const uint8_t *out = &out_data[0];
    uint8_t masked[] = {
    1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1
    };
    const uint8_t *mask = &masked[0];
    vuint8m1_t data1_v = __riscv_vle8_v_u8m1_m (mask, in1, vl);
    vuint8m1_t data2_v = __riscv_vle8_v_u8m1_m (mask, in2, vl);
    vuint8m1_t out_v = __riscv_vle8_v_u8m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrsub_vx_u8m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_u8m1 (bool8_t mask, uint8_t *out, vuint8m1_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    14, 214, 0, 0, 144, 15, 0, 0, 213, 0, 240, 252, 0, 114, 0, 61
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
