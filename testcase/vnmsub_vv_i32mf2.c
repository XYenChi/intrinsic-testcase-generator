/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    6, 29, 88, 77, -13, 127, 110, -92, 49, 80, -105, -83, 4, 77, -7, -65
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -107, 62, 127, -122, -57, -40, -11, -26, -11, -33, 72, 48, 51, 15, 18, 76
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
        out_v = __riscv_vnmsub_vv_i32mf2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32mf2 (int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    113, 29, 88, 77, 44, 167, 121, 4294967230, 49, 113, 4294967119, 4294967213, 4, 62, 4294967289, 4294967231
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
