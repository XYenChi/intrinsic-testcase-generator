/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    111, 104, -72, 88, 79, 65, 103, -2, 81, 22, -67, -39, 28, 106, -32, 13
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    87, -84, -44, -80, 110, 32, 5, 50, 36, -22, -9, 33, 60, 92, 52, 90
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
        out_v = __riscv_vmadd_vv_i32mf2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32mf2 (int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    87, 20, 4294967180, 8, 110, 97, 5, 50, 117, 4294967274, 4294967220, 4294967290, 88, 92, 52, 90
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