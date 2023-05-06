/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    27, 92, -25, -30, 34, 41, 8, -37, -33, 20, 117, 21, 59, 110, 57, 0
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    42, -55, -121, -83, 11, -121, 33, -109, -24, 94, 51, -88, -76, 125, 9, -105
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vv_i32mf2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32mf2 (int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    4294966163, 5061, 4294964271, 4294964806, 4294966923, 4961, 4294967033, 4294963264, 4294966504, 4294965417, 4294961330, 1849, 4484, 4294953547, 4294966784, 0
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
