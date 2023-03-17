/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    217, 39, 129, 216, 11, 193, 237, 186, 159, 64, 237, 213, 184, 86, 251, 37
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    230, 145, 213, 150, 248, 112, 172, 219, 28, 169, 161, 68, 210, 103, 245, 141
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    uint8_t masked[] = {
    0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1
    };
    const uint8_t *mask = &masked[0];
    vuint32m4_t data1_v = __riscv_vle32_v_u32m4 (in1, vl);
    vuint32m4_t data2_v = __riscv_vle32_v_u32m4 (in2, vl);
    vuint32m4_t out_v = __riscv_vle32_v_u32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m4 (uint32_t *out, vuint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    447, 185, 342, 367, 260, 306, 410, 405, 188, 233, 399, 282, 395, 190, 496, 179
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
