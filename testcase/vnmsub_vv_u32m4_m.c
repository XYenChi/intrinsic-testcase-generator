/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    98, 135, 180, 212, 152, 99, 71, 5, 115, 45, 1, 198, 92, 19, 21, 0
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    99, 114, 175, 169, 229, 60, 115, 165, 232, 222, 245, 155, 17, 206, 190, 213
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const uint out_data[] = {
    1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1
    };
    const uint32_t *out = &out_data[0];
    uint8_t masked[] = {
    1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0
    };
    const uint8_t *mask = &masked[0];
    vuint32m4_t data1_v = __riscv_vle32_v_u32m4_m (mask, in1, vl);
    vuint32m4_t data2_v = __riscv_vle32_v_u32m4_m (mask, in2, vl);
    vuint32m4_t out_v = __riscv_vle32_v_u32m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsub_vv_u32m4_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_u32m4 (bool32_t mask, uint32_t *out, vuint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    4294967295, 1, 0, 0, 1, 1, 4294967252, 0, 0, 0, 0, 0, 92, 4294967109, 4294967127, 1
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
