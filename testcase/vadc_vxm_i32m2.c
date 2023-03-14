/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -42, -128, -116, 21, 74, -21, -51, 103, -111, 57, -26, -73, 114, -108, -88, -33
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    107, -15, -12, -56, 105, 102, -48, -59, 48, 111, 90, -61, -63, 81, -48, -84
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    uint16_t masked[] = {
    0, 1, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0
    };
    const uint16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m2 (int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    65, -142, -128, -34, 180, 81, -98, 44, -63, 169, 64, -133, 51, -27, -135, -117
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
