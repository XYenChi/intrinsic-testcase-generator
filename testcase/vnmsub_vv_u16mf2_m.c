/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    113, 207, 219, 75, 0, 235, 65, 245, 79, 248, 17, 44, 28, 185, 137, 41
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    240, 125, 79, 5, 31, 72, 10, 14, 198, 211, 83, 108, 131, 137, 117, 30
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const uint out_data[] = {
    1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0
    };
    const uint16_t *out = &out_data[0];
    uint32_t masked[] = {
    1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1
    };
    const uint32_t *mask = &masked[0];
    vuint16mf2_t data1_v = __riscv_vle16_v_u16mf2_m (mask, in1, vl);
    vuint16mf2_t data2_v = __riscv_vle16_v_u16mf2_m (mask, in2, vl);
    vuint16mf2_t out_v = __riscv_vle16_v_u16mf2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsub_vv_u16mf2_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_u16mf2 (bool16_t mask, uint16_t *out, vuint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    65409, 82, 1, 1, 0, 163, 1, 231, 79, 37, 65470, 1, 0, 0, 137, 41
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
