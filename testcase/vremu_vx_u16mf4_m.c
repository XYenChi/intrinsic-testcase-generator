/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    32, 85, 0, 192, 134, 226, 54, 78, 159, 18, 191, 18, 212, 219, 55, 244
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    30, 0, 53, 62, 224, 81, 202, 2, 94, 184, 58, 107, 210, 182, 21, 149
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    const uint out_data[] = {
    1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0
    };
    const uint16_t *out = &out_data[0];
    uint64_t masked[] = {
    1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1
    };
    const uint64_t *mask = &masked[0];
    vuint16mf4_t data1_v = __riscv_vle16_v_u16mf4_m (mask, in1, vl);
    vuint16mf4_t data2_v = __riscv_vle16_v_u16mf4_m (mask, in2, vl);
    vuint16mf4_t out_v = __riscv_vle16_v_u16mf4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vremu_vx_u16mf4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_u16mf4 (bool16_t mask, uint16_t *out, vuint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    30, 0, 53, 0, 0, 0, 1, 2, 94, 4, 0, 0, 210, 1, 1, 149
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
