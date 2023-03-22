/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    128, 131, 13, 50, 149, 51, 192, 34, 218, 210, 102, 152, 119, 1, 179, 247
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    188, 139, 254, 115, 225, 105, 166, 10, 181, 213, 206, 44, 211, 213, 185, 217
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
        out_v = __riscv_vmul_vx_i8m4 (data1_v, data2_v, vl);
        void __riscv_vse8_v_u8m4 (uint8_t *out, vuint8m4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    0, 33, 230, 118, 245, 235, 128, 84, 34, 186, 20, 32, 21, 213, 91, 95
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
