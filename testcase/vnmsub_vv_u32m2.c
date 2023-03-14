/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    185, 56, 198, 133, 161, 201, 226, 168, 150, 141, 39, 189, 63, 232, 153, 170
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    105, 176, 75, 198, 10, 43, 171, 126, 92, 136, 43, 175, 214, 144, 95, 99
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32m2_t data1_v = __riscv_vle32_v_u32m2 (in1, vl);
    vuint32m2_t data2_v = __riscv_vle32_v_u32m2 (in2, vl);
    vuint32m2_t out_v = __riscv_vle32_v_u32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsub_vv_u32m2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_u32m2 (uint32_t *out, vuint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    185, 4294967176, 123, 133, 151, 158, 55, 168, 150, 5, 39, 14, 4294967145, 88, 58, 170
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
