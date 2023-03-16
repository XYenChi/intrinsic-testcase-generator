/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    -119, 23, -122, -15, -115, 79, 77, 30, 87, 78, 64, 55, -83, -115, -11, 26
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    56, 101, -92, 65, -28, 85, -111, 102, -100, -111, -43, 72, -44, 27, 20, -119
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e8m2(avl);
    uint4_t masked[] = {
    0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0
    };
    const uint4_t *mask = &masked[0];
    vint8m2_t data1_v = __riscv_vle8_v_i8m2 (in1, vl);
    vint8m2_t data2_v = __riscv_vle8_v_i8m2 (in2, vl);
    vint8m2_t out_v = __riscv_vle8_v_i8m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse8_v_i8m2 (int8_t *out, vint8m2_t out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -63, 124, -213, 50, -142, 164, -34, 132, -12, -33, 22, 128, -126, -88, 9, -93
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