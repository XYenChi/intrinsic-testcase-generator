/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    145, 134, 63, 177, 134, 149, 147, 82, 127, 138, 6, 69, 249, 185, 157, 141
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    136, 179, 4, 115, 39, 143, 189, 62, 206, 183, 136, 20, 8, 233, 148, 154
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf4(avl);
    uint32_t masked[] = {
    1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0
    };
    const uint32_t *mask = &masked[0];
    vuint8mf4_t data1_v = __riscv_vle8_v_u8mf4 (in1, vl);
    vuint8mf4_t data2_v = __riscv_vle8_v_u8mf4 (in2, vl);
    vuint8mf4_t out_v = __riscv_vle8_v_u8mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_u8mf4 (uint8_t *out, vuint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    282, 313, 68, 293, 173, 292, 336, 145, 333, 322, 143, 89, 258, 418, 305, 295
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
