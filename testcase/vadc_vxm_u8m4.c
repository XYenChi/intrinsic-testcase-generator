/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    28, 132, 159, 210, 18, 202, 189, 22, 148, 123, 177, 221, 10, 17, 102, 103
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    103, 113, 88, 155, 179, 132, 76, 125, 193, 8, 188, 199, 129, 235, 164, 40
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m4(avl);
    uint2_t masked[] = {
    1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1
    };
    const uint2_t *mask = &masked[0];
    vuint8m4_t data1_v = __riscv_vle8_v_u8m4 (in1, vl);
    vuint8m4_t data2_v = __riscv_vle8_v_u8m4 (in2, vl);
    vuint8m4_t out_v = __riscv_vle8_v_u8m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_u8m4 (uint8_t *out, vuint8m4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    132, 246, 247, 366, 197, 334, 266, 147, 342, 132, 365, 421, 139, 252, 266, 144
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
