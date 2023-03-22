/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint32_t data1[] = {
    14, 133, 173, 10, 62, 127, 82, 247, 150, 151, 215, 182, 80, 56, 152, 9
    };
    const uint32_t *in1 = &data1[0];
    const uint32_t data2[] = {
    201, 212, 142, 117, 45, 210, 200, 190, 69, 199, 86, 115, 224, 84, 160, 224
    };
    const uint32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    uint64_t masked[] = {
    1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0
    };
    const uint64_t *mask = &masked[0];
    vuint32mf2_t data1_v = __riscv_vle32_v_u32mf2 (in1, vl);
    vuint32mf2_t data2_v = __riscv_vle32_v_u32mf2 (in2, vl);
    vuint32mf2_t out_v = __riscv_vle32_v_u32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vxm_u32mf2 (data1_v, data2_v, masked size_t vl);
        void __riscv_vse32_v_u32mf2 (uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    uint32_t golden[] = {
    201, 133, 173, 117, 45, 210, 82, 247, 69, 151, 86, 115, 80, 56, 152, 9
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
