/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    28, 91, -128, 70, 16, 13, -101, 10, 28, -65, -46, 18, -39, -17, -4, -99
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    59, 85, 89, -3, -17, -57, 100, -64, 63, 71, -1, -80, 60, -98, 84, 82
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    uint8_t masked[] = {
    1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1
    };
    const uint8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vvm_i32m4 (data1_v, data2_v, masked, vl);
        void __riscv_vse32_v_i32m4 (int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    88, 177, -39, 68, 0, -44, 0, -53, 92, 7, -46, -61, 22, -115, 80, -16
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
