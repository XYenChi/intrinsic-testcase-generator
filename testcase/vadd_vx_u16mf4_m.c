/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    26454, 209, 36188, 18095, 55603, 47353, 16919, 54823, 18621, 11465, 28468, 42082, 50319, 58539, 62314, 19195
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    8634, 56008, 8991, 34357, 4566, 52970, 23824, 62709, 31812, 61583, 64930, 4584, 1921, 20534, 53023, 9077
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    const uint out_data[] = {
    0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0
    };
    const uint16_t *out = &out_data[0];
    uint64_t masked[] = {
    1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0
    };
    const uint64_t *mask = &masked[0];
    vuint16mf4_t data1_v = __riscv_vle16_v_u16mf4 (in1, vl);
    vuint16mf4_t data2_v = __riscv_vle16_v_u16mf4 (in2, vl);
    vuint16mf4_t out_v = __riscv_vle16_v_u16mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16mf4 (uint16_t *out, vuint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    35088, 56217, 1, 1, 0, 0, 0, 51996, 50433, 7512, 27862, 46666, 52240, 1, 49801, 0
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
