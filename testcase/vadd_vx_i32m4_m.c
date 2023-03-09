/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    73, 38, -119, -93, 68, -15, 37, 25, 70, 20, -74, -2, 36, -19, -71, 108
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    115, -121, 116, 88, -91, -31, -100, -113, 68, -87, 90, 126, -7, 11, -87, -29
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int out_data[] = {
    -11, -104, -64, -74, 119, 47, 61, -117, -110, -101, 14, -89, -47, -109, -98, -11
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m4 (bool32_t mask, int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    188, 4294967213, 4294967232, 4294967291, 119, 47, 61, 4294967179, 138, 4294967195, 16, 124, 4294967249, 4294967187, 4294967138, 79
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
