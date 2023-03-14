/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    224, 1, 124, 97, 210, 240, 88, 116, 190, 215, 206, 201, 245, 32, 35, 8
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    138, 127, 28, 198, 40, 166, 101, 43, 214, 155, 169, 73, 35, 35, 57, 163
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m8(avl);
    const uint out_data[] = {
    1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0
    };
    const uint8_t *out = &out_data[0];
    uint1_t masked[] = {
    0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1
    };
    const uint1_t *mask = &masked[0];
    vuint8m8_t data1_v = __riscv_vle8_v_u8m8_m (mask, in1, vl);
    vuint8m8_t data2_v = __riscv_vle8_v_u8m8_m (mask, in2, vl);
    vuint8m8_t out_v = __riscv_vle8_v_u8m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vx_u8m8_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse8_v_u8m8 (bool8_t mask, uint8_t *out, vuint8m8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    1, 129, 1, 0, 49, 97, 73, 133, 45, 212, 3, 1, 1, 0, 53, 232
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
