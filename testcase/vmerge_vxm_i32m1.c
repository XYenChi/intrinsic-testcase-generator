/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    64, -36, 39, 101, -122, 46, 115, -26, 13, 117, 16, 28, -90, 72, -94, -20
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -79, 65, -125, 15, -49, -62, -55, 19, -9, 114, -64, 72, -98, 50, -18, -11
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    uint32_t masked[] = {
    0, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1
    };
    const uint32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vxm_i32m1 (data1_v, data2_v, masked size_t vl);
        void __riscv_vse32_v_i32m1 (int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    64, 65, 39, 101, -122, -62, -55, 19, -9, 117, 16, 72, -90, 72, -94, -11
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
