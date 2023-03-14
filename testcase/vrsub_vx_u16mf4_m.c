/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    103, 63, 210, 202, 135, 198, 148, 38, 53, 117, 191, 79, 221, 180, 178, 141
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    9, 9, 141, 114, 206, 193, 9, 61, 108, 174, 238, 165, 108, 207, 118, 197
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    const uint out_data[] = {
    0, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1
    };
    const uint16_t *out = &out_data[0];
    uint64_t masked[] = {
    0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0
    };
    const uint64_t *mask = &masked[0];
    vuint16mf4_t data1_v = __riscv_vle16_v_u16mf4_m (mask, in1, vl);
    vuint16mf4_t data2_v = __riscv_vle16_v_u16mf4_m (mask, in2, vl);
    vuint16mf4_t out_v = __riscv_vle16_v_u16mf4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrsub_vx_u16mf4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_u16mf4 (bool16_t mask, uint16_t *out, vuint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    0, 65482, 65467, 65448, 0, 0, 65397, 1, 55, 57, 0, 1, 0, 0, 65476, 1
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
