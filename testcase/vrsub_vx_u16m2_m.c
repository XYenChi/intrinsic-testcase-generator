/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    191, 228, 219, 117, 18, 134, 185, 34, 224, 179, 108, 89, 11, 238, 243, 24
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    19, 63, 231, 15, 158, 28, 90, 207, 227, 181, 238, 22, 62, 157, 31, 212
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    const uint out_data[] = {
    1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1
    };
    const uint16_t *out = &out_data[0];
    uint8_t masked[] = {
    1, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0
    };
    const uint8_t *mask = &masked[0];
    vuint16m2_t data1_v = __riscv_vle16_v_u16m2_m (mask, in1, vl);
    vuint16m2_t data2_v = __riscv_vle16_v_u16m2_m (mask, in2, vl);
    vuint16m2_t out_v = __riscv_vle16_v_u16m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrsub_vx_u16m2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_u16m2 (bool16_t mask, uint16_t *out, vuint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    65364, 65371, 1, 1, 0, 65430, 0, 173, 1, 1, 0, 1, 0, 65455, 1, 1
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
