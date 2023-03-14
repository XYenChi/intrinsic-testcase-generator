/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    210, 50, 43, 13, 189, 67, 223, 12, 13, 56, 31, 122, 94, 241, 97, 216
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    137, 0, 101, 164, 231, 93, 4, 254, 86, 99, 146, 39, 107, 156, 229, 136
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const uint out_data[] = {
    1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0
    };
    const uint16_t *out = &out_data[0];
    uint32_t masked[] = {
    1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1
    };
    const uint32_t *mask = &masked[0];
    vuint16mf2_t data1_v = __riscv_vle16_v_u16mf2_m (mask, in1, vl);
    vuint16mf2_t data2_v = __riscv_vle16_v_u16mf2_m (mask, in2, vl);
    vuint16mf2_t out_v = __riscv_vle16_v_u16mf2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16mf2 (bool16_t mask, uint16_t *out, vuint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    420, 50, 86, 13, 378, 134, 223, 12, 13, 112, 31, 244, 188, 241, 194, 216
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
