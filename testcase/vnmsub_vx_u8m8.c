/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    205, 3, 16, 254, 154, 249, 43, 132, 50, 5, 94, 129, 23, 203, 110, 131
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    82, 128, 9, 40, 211, 186, 150, 227, 57, 198, 34, 115, 241, 255, 170, 62
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m8(avl);
    const uint8_t out_data[16];
    const uint8_t *out = &out_data[0];
    vuint8m8_t data1_v = __riscv_vle8_v_u8m8 (in1, vl);
    vuint8m8_t data2_v = __riscv_vle8_v_u8m8 (in2, vl);
    vuint8m8_t out_v = __riscv_vle8_v_u8m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsub_vx_u8m8 (out_data, data1_v, data2_v, vl);
        void __riscv_vse8_v_u8m8 (uint8_t *out, vuint8m8_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    123, 131, 7, 254, 154, 249, 149, 161, 50, 5, 94, 129, 38, 204, 110, 131
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
