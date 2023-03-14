/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    186, 150, 47, 42, 114, 108, 183, 170, 130, 246, 62, 201, 97, 222, 59, 229
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    149, 105, 50, 71, 124, 85, 40, 149, 59, 132, 254, 81, 115, 85, 214, 80
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16m8_t data1_v = __riscv_vle16_v_u16m8 (in1, vl);
    vuint16m8_t data2_v = __riscv_vle16_v_u16m8 (in2, vl);
    vuint16m8_t out_v = __riscv_vle16_v_u16m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrsub_vx_u16m8 (data1_v, data2_v, vl);
        void __riscv_vse16_v_u16m8 (uint16_t *out, vuint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    65499, 65491, 3, 29, 10, 65513, 65393, 65515, 65465, 65422, 192, 65416, 18, 65399, 155, 65387
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
