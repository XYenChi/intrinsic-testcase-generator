/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    11, 53, -16, 35, -125, 11, -78, -33, -21, -7, 123, -41, 72, -97, 25, 34
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -104, -67, -100, 115, -80, -7, -41, 54, -104, -69, 65, -116, 36, -39, -119, -2
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int out_data[] = {
    1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0
    };
    const int32_t *out = &out_data[0];
    uint4_t masked[] = {
    0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1
    };
    const uint4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsub_vv_i32m8_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m8 (bool32_t mask, int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1, 1, 4294967280, 1, 4294967171, 0, 4294967218, 4294967263, 4294967275, 4294967289, 58, 0, 72, 4294967238, 0, 34
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
