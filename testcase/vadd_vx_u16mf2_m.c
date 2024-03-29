/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    12143, 2924, 16579, 51612, 12339, 53431, 23493, 35721, 29452, 21177, 32916, 42473, 11805, 18656, 41181, 7944
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    1725, 35520, 42810, 42971, 30956, 5896, 52937, 44808, 55832, 47221, 14817, 10045, 16131, 5324, 64695, 41831
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const uint out_data[] = {
    1, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1
    };
    const uint16_t *out = &out_data[0];
    uint32_t masked[] = {
    0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 1, 0
    };
    const uint32_t *mask = &masked[0];
    vuint16mf2_t data1_v = __riscv_vle16_v_u16mf2 (in1, vl);
    vuint16mf2_t data2_v = __riscv_vle16_v_u16mf2 (in2, vl);
    vuint16mf2_t out_v = __riscv_vle16_v_u16mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16mf2 (uint16_t *out, vuint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    1, 0, 1, 29047, 43295, 1, 1, 1, 19748, 0, 1, 52518, 27936, 0, 40340, 1
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
