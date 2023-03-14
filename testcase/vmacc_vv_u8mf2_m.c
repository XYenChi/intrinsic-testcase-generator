/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    29, 17, 4, 136, 186, 237, 26, 98, 195, 188, 152, 246, 118, 245, 219, 230
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    132, 54, 223, 235, 77, 220, 65, 166, 242, 171, 101, 33, 215, 111, 126, 29
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf2(avl);
    const uint out_data[] = {
    0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0
    };
    const uint8_t *out = &out_data[0];
    uint16_t masked[] = {
    1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 0
    };
    const uint16_t *mask = &masked[0];
    vuint8mf2_t data1_v = __riscv_vle8_v_u8mf2_m (mask, in1, vl);
    vuint8mf2_t data2_v = __riscv_vle8_v_u8mf2_m (mask, in2, vl);
    vuint8mf2_t out_v = __riscv_vle8_v_u8mf2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_u8mf2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse8_v_u8mf2 (bool8_t mask, uint8_t *out, vuint8mf2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    244, 150, 1, 217, 242, 173, 1, 140, 86, 0, 248, 183, 1, 0, 202, 0
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
