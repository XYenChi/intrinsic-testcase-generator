/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    34, 190, 7, 175, 42, 237, 142, 136, 55, 244, 147, 204, 87, 84, 171, 220
    };
    const uint32_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const uint out_data[] = {
    1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1
    };
    const uint32_t *out = &out_data[0];
    uint4_t masked[] = {
    1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1
    };
    const uint4_t *mask = &masked[0];
    vuint32m8_t data1_v = __riscv_vle32_v_u32m8_m (mask, in1, vl);
    vuint32m8_t out_v = __riscv_vle32_v_u32m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnot_v_u32m8 (mask, data1_v, vl);
        void __riscv_vse32_v_u32m8 (bool32_t mask, uint32_t *out, vuint32m8_t out_v, size_t vl);
        in1 += 4;
    uint32_t golden[] = {
    -35, -191, 1, -176, -43, -238, -143, -137, 1, 1, -148, -205, -88, -85, 1, -221
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
