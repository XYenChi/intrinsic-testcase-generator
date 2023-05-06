/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -25, -76, 23, -49, -61, 115, 25, 114, 23, 114, -83, 72, -115, 22, -1, 18
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    99, 74, -70, 74, -36, -37, 38, -66, 56, 77, -77, 44, -89, 35, -123, 22
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (in1, vl);
    vuint32m8_t data2_v = __riscv_vle32_v_i32m8 (in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vwmul_vv_i32m8 (out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m8 (int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    4294964821, 4294961672, 4294965686, 4294963670, 2196, 4294963041, 950, 4294959772, 1288, 8778, 6391, 3168, 10235, 770, 123, 396
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
