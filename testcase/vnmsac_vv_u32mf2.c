/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    78, 102, 231, 234, 250, 18, 63, 23, 65, 167, 202, 213, 185, 93, 33, 16
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    23, 55, 206, 46, 68, 156, 126, 85, 71, 92, 200, 80, 208, 124, 170, 85
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const uint32_t out_data[16];
    const uint32_t *out = &out_data[0];
    vuint32mf2_t data1_v = __riscv_vle32_v_u32mf2 (in1, vl);
    vuint32mf2_t data2_v = __riscv_vle32_v_u32mf2 (in2, vl);
    vuint32mf2_t out_v = __riscv_vle32_v_u32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vv_u32mf2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_u32mf2 (uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    uint32_t golden[] = {
    4294965502, 4294961687, 4294919710, 4294956533, 4294950297, 4294964489, 4294959358, 4294965341, 4294962682, 4294951932, 4294926897, 4294950257, 4294928816, 4294955764, 4294961687, 4294965936
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
