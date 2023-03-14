/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    38, 66, 101, 191, 118, 151, 154, 191, 215, 97, 151, 197, 176, 170, 250, 3
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    46, 56, 15, 10, 206, 52, 3, 92, 77, 244, 176, 142, 137, 242, 203, 124
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    uint16_t masked[] = {
    0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0
    };
    const uint16_t *mask = &masked[0];
    vuint32m2_t data1_v = __riscv_vle32_v_u32m2 (in1, vl);
    vuint32m2_t data2_v = __riscv_vle32_v_u32m2 (in2, vl);
    vuint32m2_t out_v = __riscv_vle32_v_u32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m2 (uint32_t *out, vuint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    84, 122, 116, 201, 324, 203, 157, 284, 292, 341, 327, 339, 313, 412, 454, 127
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
