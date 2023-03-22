/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -77, -5, 66, -20, -117, 63, -108, -14, -70, -48, 49, -74, 3, 7, -19, 4
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    84, -74, -47, 64, 89, 93, -110, 3, -61, -82, 99, -83, 74, 119, 110, -14
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    uint4_t masked[] = {
    1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1
    };
    const uint4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vxm_i32m8 (data1_v, data2_v, masked, vl);
        void __riscv_vse32_v_i32m8 (int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    8, -78, 19, 44, -27, 157, -217, -10, -130, -129, 148, -157, 77, 126, 91, -9
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
