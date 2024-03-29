/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    102, 93, 55, 25, 49, 106, 231, 173, 91, 49, 2, 138, 187, 138, 190, 96
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    134, 173, 42, 226, 186, 248, 178, 50, 70, 251, 88, 11, 182, 92, 208, 138
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m8(avl);
    const uint out_data[] = {
    1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1
    };
    const uint8_t *out = &out_data[0];
    uint1_t masked[] = {
    1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1
    };
    const uint1_t *mask = &masked[0];
    vuint8m8_t data1_v = __riscv_vle8_v_u8m8 (in1, vl);
    vuint8m8_t data2_v = __riscv_vle8_v_u8m8 (in2, vl);
    vuint8m8_t out_v = __riscv_vle8_v_u8m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_u8m8 (uint8_t *out, vuint8m8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    236, 1, 1, 251, 0, 98, 153, 0, 161, 1, 0, 149, 0, 0, 142, 234
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
