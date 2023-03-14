/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    127, 135, 97, 159, 35, 29, 230, 89, 243, 150, 193, 37, 110, 124, 93, 70
    };
    const uint32_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m4_t data1_v = __riscv_vle32_v_u32m4 (in1, vl);
    vuint32m4_t out_v = __riscv_vle32_v_u32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vneg_v_32m4 (data1_v, vl);
        void __riscv_vse32_v_u32m4 (uint32_t *out, vuint32m4_t out_v, size_t vl);
        in1 += 4;
    uint32_t golden[] = {
    -127, -135, -97, -159, -35, -29, -230, -89, -243, -150, -193, -37, -110, -124, -93, -70
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
