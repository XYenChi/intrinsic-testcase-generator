/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4084781465, 3149776503, 3670614780, 318048773, 285736405, 3507477402, 593778442, 680498390, 3938676731, 3734418429, 2819502425, 894475777, 408028692, 4055550455, 2783303305, 4067034873
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1900127516, 3276215171, 1714552194, 1656496967, 2262558924, 2851887252, 688311374, 573064534, 2365772915, 3360335846, 383584142, 2525167446, 3812742276, 3978366234, 3516520328, 4076494293
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, size_t vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1900127516, 3276215171, 1714552194, 1656496967, 2262558924, 2851887252, 688311374, 573064534, 2365772915, 3360335846, 383584142, 2525167446, 3812742276, 3978366234, 3516520328, 4076494293
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
