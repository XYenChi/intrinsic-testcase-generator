/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    99, -55, -25, -58, -50, -121, -113, -42, 66, -46, -26, 70, -20, 20, -91, -1
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -98, 58, -34, 19, -110, 55, 116, 36, 87, -16, -111, 38, -80, -69, 16, -123
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int out_data[] = {
    11, 91, -61, -123, -3, -12, 13, 18, -117, 49, 17, -53, -121, 35, 99, 100
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m2 (bool32_t mask, int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    11, 91, 4294967237, 4294967173, 4294967136, 4294967230, 13, 18, 153, 49, 4294967159, 108, 4294967196, 4294967247, 99, 4294967172
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
