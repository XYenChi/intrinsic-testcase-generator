/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    15, 82, 166, 117, 180, 31, 52, 102, 131, 18, 197, 112, 32, 178, 173, 25
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    54, 137, 78, 141, 177, 63, 217, 250, 112, 11, 194, 40, 164, 54, 192, 177
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const uint out_data[] = {
    0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1
    };
    const uint32_t *out = &out_data[0];
    uint8_t masked[] = {
    1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0
    };
    const uint8_t *mask = &masked[0];
    vuint32m4_t data1_v = __riscv_vle32_v_u32m4_m (mask, in1, vl);
    vuint32m4_t data2_v = __riscv_vle32_v_u32m4_m (mask, in2, vl);
    vuint32m4_t out_v = __riscv_vle32_v_u32m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrsub_vx_u32m4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_u32m4 (bool32_t mask, uint32_t *out, vuint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    39, 1, 0, 0, 0, 0, 1, 148, 4294967277, 4294967289, 1, 4294967224, 1, 1, 0, 1
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
