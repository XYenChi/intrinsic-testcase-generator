/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    248, 41, 104, 94, 87, 101, 199, 239, 76, 254, 88, 177, 2, 128, 247, 31
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    224, 136, 221, 210, 183, 237, 31, 156, 1, 208, 62, 50, 107, 68, 186, 18
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf4(avl);
    const uint out_data[] = {
    0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 1
    };
    const uint8_t *out = &out_data[0];
    uint32_t masked[] = {
    1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1
    };
    const uint32_t *mask = &masked[0];
    vuint8mf4_t data1_v = __riscv_vle8_v_u8mf4_m (mask, in1, vl);
    vuint8mf4_t data2_v = __riscv_vle8_v_u8mf4_m (mask, in2, vl);
    vuint8mf4_t out_v = __riscv_vle8_v_u8mf4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_u8mf4 (bool8_t mask, uint8_t *out, vuint8mf4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    248, 136, 221, 1, 183, 237, 0, 0, 0, 1, 88, 177, 107, 128, 1, 31
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
