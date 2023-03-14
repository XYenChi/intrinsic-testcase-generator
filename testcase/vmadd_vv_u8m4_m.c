/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    181, 159, 84, 138, 32, 117, 165, 189, 250, 149, 24, 230, 207, 175, 107, 132
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    176, 25, 184, 26, 17, 67, 19, 238, 228, 236, 67, 181, 43, 195, 97, 35
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m4(avl);
    const uint out_data[] = {
    1, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1
    };
    const uint8_t *out = &out_data[0];
    uint2_t masked[] = {
    0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1
    };
    const uint2_t *mask = &masked[0];
    vuint8m4_t data1_v = __riscv_vle8_v_u8m4_m (mask, in1, vl);
    vuint8m4_t data2_v = __riscv_vle8_v_u8m4_m (mask, in2, vl);
    vuint8m4_t out_v = __riscv_vle8_v_u8m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmadd_vv_u8m4_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse8_v_u8m4 (bool8_t mask, uint8_t *out, vuint8m4_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    181, 159, 184, 138, 32, 67, 19, 189, 250, 129, 91, 181, 207, 175, 204, 167
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
