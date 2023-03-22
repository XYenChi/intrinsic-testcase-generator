/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    79, -85, 104, -15, 94, 55, -2, -128, -64, -5, 83, 83, -110, -44, -40, -10
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -108, 67, -48, -28, -77, -85, -29, -108, 25, 63, 90, 121, 78, -53, 36, -114
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vx_i32m4 (out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m4 (int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    8533, 5695, 4993, 4294966877, 7239, 4675, 4294967239, 4294953472, 1601, 316, 4294959826, 4294957253, 8580, 4294964964, 1441, 4294966157
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
