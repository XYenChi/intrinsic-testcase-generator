/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    190, 253, 233, 133, 65, 148, 104, 212, 19, 156, 27, 161, 12, 88, 217, 62
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    117, 219, 149, 41, 81, 145, 121, 82, 165, 80, 54, 0, 75, 229, 16, 127
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m2(avl);
    const uint out_data[] = {
    1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0
    };
    const uint8_t *out = &out_data[0];
    uint4_t masked[] = {
    0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0
    };
    const uint4_t *mask = &masked[0];
    vuint8m2_t data1_v = __riscv_vle8_v_u8m2_m (mask, in1, vl);
    vuint8m2_t data2_v = __riscv_vle8_v_u8m2_m (mask, in2, vl);
    vuint8m2_t out_v = __riscv_vle8_v_u8m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_u8m2 (bool8_t mask, uint8_t *out, vuint8m2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    1, 1, 1, 41, 81, 145, 0, 82, 165, 0, 1, 1, 0, 229, 16, 0
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
