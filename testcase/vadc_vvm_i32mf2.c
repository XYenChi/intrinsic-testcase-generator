/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -45, 124, -6, 19, -105, -104, -4, -107, 76, -119, -21, -25, 92, -113, 115, -60
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -53, 102, 58, -56, -108, -3, 31, -16, -35, 46, -82, 91, -74, -117, 23, 87
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    uint64_t masked[] = {
    1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0
    };
    const uint64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vvm_i32mf2 (data1_v, data2_v, masked, vl);
        void __riscv_vse32_v_i32mf2 (int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -97, 227, 53, -36, -213, -107, 27, -122, 42, -73, -103, 66, 18, -230, 138, 27
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
