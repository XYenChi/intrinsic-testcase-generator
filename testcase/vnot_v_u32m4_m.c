/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    159, 139, 233, 127, 179, 191, 180, 123, 48, 60, 199, 39, 222, 170, 126, 113
    };
    const uint32_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const uint out_data[] = {
    1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1
    };
    const uint32_t *out = &out_data[0];
    uint8_t masked[] = {
    0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1
    };
    const uint8_t *mask = &masked[0];
    vuint32m4_t data1_v = __riscv_vle32_v_u32m4_m (mask, in1, vl);
    vuint32m4_t out_v = __riscv_vle32_v_u32m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnot_v_u32m4 (mask, data1_v, vl);
        void __riscv_vse32_v_u32m4 (bool32_t mask, uint32_t *out, vuint32m4_t out_v, size_t vl);
        in1 += 4;
    uint32_t golden[] = {
    1, -140, 0, 0, -180, -192, -181, -124, -49, 1, -200, 1, 1, -171, 0, -114
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
