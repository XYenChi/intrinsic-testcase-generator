/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    28, -18, 91, -107, -43, 65, -57, 13, 67, -52, -109, -100, 111, -80, -41, 25
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -123, -89, -88, 21, 83, 111, -88, 53, -34, 67, 27, -90, 23, 54, -19, 69
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    const int out_data[] = {
    -47, -67, 93, -66, 105, -40, 12, -124, -34, 15, 82, -101, -71, 13, 0, -47
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m8 (bool32_t mask, int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    4294967201, 4294967229, 93, 4294967210, 105, 176, 12, 66, 4294967262, 15, 82, 4294967106, 4294967225, 13, 4294967236, 4294967249
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
