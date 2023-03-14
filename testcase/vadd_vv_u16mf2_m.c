/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    245, 162, 57, 54, 30, 255, 212, 113, 62, 35, 17, 94, 201, 3, 114, 232
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    184, 161, 62, 184, 214, 234, 179, 148, 117, 16, 241, 244, 58, 62, 36, 166
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const uint out_data[] = {
    0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1
    };
    const uint16_t *out = &out_data[0];
    uint32_t masked[] = {
    0, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0
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
    0, 323, 1, 238, 0, 1, 391, 261, 1, 0, 258, 338, 0, 1, 150, 1
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
