/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    221, 66, 236, 203, 34, 141, 77, 139, 74, 86, 195, 37, 206, 182, 242, 247
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    62, 215, 164, 151, 22, 126, 24, 109, 87, 228, 151, 221, 10, 35, 74, 210
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    uint32_t masked[] = {
    1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0
    };
    const uint32_t *mask = &masked[0];
    vuint16mf2_t data1_v = __riscv_vle16_v_u16mf2 (in1, vl);
    vuint16mf2_t data2_v = __riscv_vle16_v_u16mf2 (in2, vl);
    vuint16mf2_t out_v = __riscv_vle16_v_u16mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16mf2 (uint16_t *out, vuint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    uint16_t golden[] = {
    62, 215, 236, 151, 34, 141, 24, 139, 87, 228, 195, 37, 206, 182, 74, 247
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
