/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    113, 178, 100, 167, 228, 130, 89, 44, 96, 82, 9, 194, 43, 159, 192, 90
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    170, 159, 20, 44, 65, 17, 237, 193, 217, 70, 161, 53, 19, 9, 197, 230
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m4(avl);
    const uint8_t out_data[16];
    const uint8_t *out = &out_data[0];
    vuint8m4_t data1_v = __riscv_vle8_v_u8m4 (in1, vl);
    vuint8m4_t data2_v = __riscv_vle8_v_u8m4 (in2, vl);
    vuint8m4_t out_v = __riscv_vle8_v_u8m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vx_u8m4 (out_data, data1_v, data2_v, vl);
        void __riscv_vse8_v_u8m4 (uint8_t *out, vuint8m4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    246, 114, 48, 76, 28, 95, 155, 212, 161, 149, 87, 215, 207, 105, 65, 37
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
