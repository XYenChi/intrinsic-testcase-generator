/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    131, 27, 131, 20, 180, 108, 232, 232, 198, 58, 0, 172, 195, 216, 18, 7
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    27, 117, 87, 187, 93, 2, 189, 27, 13, 0, 205, 199, 162, 142, 146, 244
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const uint out_data[] = {
    1, 1, 0, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0
    };
    const uint32_t *out = &out_data[0];
    uint16_t masked[] = {
    1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1
    };
    const uint16_t *mask = &masked[0];
    vuint32m2_t data1_v = __riscv_vle32_v_u32m2_m (mask, in1, vl);
    vuint32m2_t data2_v = __riscv_vle32_v_u32m2_m (mask, in2, vl);
    vuint32m2_t out_v = __riscv_vle32_v_u32m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vx_u32m2_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_u32m2 (bool32_t mask, uint32_t *out, vuint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    4294963760, 4294964138, 0, 0, 1, 0, 0, 4294961033, 4294964723, 0, 1, 1, 4294935706, 4294936624, 4294964668, 4294965588
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
