/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    88, 174, 161, 99, 81, 55, 79, 106, 37, 198, 81, 81, 204, 69, 128, 35
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    106, 100, 76, 35, 77, 123, 53, 66, 171, 254, 208, 247, 253, 27, 139, 227
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m1(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16m1_t data1_v = __riscv_vle16_v_u16m1 (in1, vl);
    vuint16m1_t data2_v = __riscv_vle16_v_u16m1 (in2, vl);
    vuint16m1_t out_v = __riscv_vle16_v_u16m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vwmaccu_vv_u16m1 (out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_u16m1 (uint16_t *out, vuint16m1_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    9329, 17400, 12237, 3466, 6237, 6765, 4188, 6997, 6327, 50292, 16849, 20008, 51612, 1864, 17792, 7945
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
