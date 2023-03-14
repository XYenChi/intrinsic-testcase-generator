/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    211, 99, 81, 4, 153, 106, 26, 30, 230, 226, 227, 246, 134, 111, 186, 209
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    30, 134, 234, 40, 34, 147, 95, 186, 190, 206, 112, 7, 117, 32, 39, 128
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16mf2_t data1_v = __riscv_vle16_v_u16mf2 (in1, vl);
    vuint16mf2_t data2_v = __riscv_vle16_v_u16mf2 (in2, vl);
    vuint16mf2_t out_v = __riscv_vle16_v_u16mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vx_u16mf2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_u16mf2 (uint16_t *out, vuint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    59207, 52271, 46582, 65377, 60334, 49954, 63066, 59956, 21837, 18981, 40112, 63815, 49858, 61984, 58283, 38784
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
