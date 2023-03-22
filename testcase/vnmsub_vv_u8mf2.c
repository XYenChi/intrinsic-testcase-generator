/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    79, 42, 160, 72, 235, 246, 225, 78, 25, 196, 104, 90, 44, 145, 227, 53
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    99, 93, 105, 143, 195, 45, 29, 169, 46, 10, 26, 190, 178, 124, 135, 121
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8mf2(avl);
    const uint8_t out_data[16];
    const uint8_t *out = &out_data[0];
    vuint8mf2_t data1_v = __riscv_vle8_v_u8mf2 (in1, vl);
    vuint8mf2_t data2_v = __riscv_vle8_v_u8mf2 (in2, vl);
    vuint8mf2_t out_v = __riscv_vle8_v_u8mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsub_vv_u8mf2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse8_v_u8mf2 (uint8_t *out, vuint8mf2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    uint8_t golden[] = {
    236, 42, 55, 185, 235, 201, 196, 78, 25, 186, 104, 156, 122, 145, 227, 53
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
