/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    201, 226, 20, 26, 254, 212, 11, 228, 245, 140, 219, 134, 172, 20, 105, 129
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    170, 27, 245, 62, 90, 176, 218, 178, 121, 26, 207, 224, 66, 83, 122, 234
    };
    const int32_t *in2 = &data2[0];
    const int32_t out_data[16];
    int32_t *out = &out_data[0];
    vint32m2_t __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        vint32m2_t out_data = __riscv_vadd_vx_i32m2 (data1, data2, vl)
        vint32m2_t __riscv_vse32_v_i32m2 (out, out_data, vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    371, 253, 265, 88, 344, 388, 229, 406, 366, 166, 426, 358, 238, 103, 227, 363
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
