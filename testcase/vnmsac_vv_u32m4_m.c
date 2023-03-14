/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    190, 109, 199, 155, 226, 111, 93, 148, 49, 116, 242, 129, 222, 232, 247, 84
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    190, 22, 169, 128, 222, 79, 229, 205, 206, 217, 81, 85, 196, 161, 137, 199
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const uint out_data[] = {
    1, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 1
    };
    const uint32_t *out = &out_data[0];
    uint8_t masked[] = {
    1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0
    };
    const uint8_t *mask = &masked[0];
    vuint32m4_t data1_v = __riscv_vle32_v_u32m4_m (mask, in1, vl);
    vuint32m4_t data2_v = __riscv_vle32_v_u32m4_m (mask, in2, vl);
    vuint32m4_t out_v = __riscv_vle32_v_u32m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vv_u32m4_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_u32m4 (bool32_t mask, uint32_t *out, vuint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    4294931197, 0, 1, 1, 4294917124, 4294958527, 4294945999, 4294936957, 0, 4294942125, 1, 0, 4294923784, 1, 4294933458, 1
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
