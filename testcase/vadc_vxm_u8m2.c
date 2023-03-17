/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint8_t data1[] = {
    163, 188, 122, 188, 115, 192, 97, 4, 112, 236, 160, 1, 193, 31, 46, 229
    };
    const uint8_t *in1 = &data1[0];
    const uint8_t data2[] = {
    121, 208, 95, 206, 126, 20, 85, 109, 147, 60, 120, 35, 78, 37, 195, 59
    };
    const uint8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m2(avl);
    uint4_t masked[] = {
    1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1
    };
    const uint4_t *mask = &masked[0];
    vuint8m2_t data1_v = __riscv_vle8_v_u8m2 (in1, vl);
    vuint8m2_t data2_v = __riscv_vle8_v_u8m2 (in2, vl);
    vuint8m2_t out_v = __riscv_vle8_v_u8m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_u8m2 (uint8_t *out, vuint8m2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    uint8_t golden[] = {
    285, 397, 218, 395, 242, 213, 182, 114, 259, 296, 280, 37, 271, 69, 241, 289
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
