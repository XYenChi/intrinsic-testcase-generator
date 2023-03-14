/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    71, 29, -47, -98, -39, 35, 126, 66, -104, -122, -82, 18, 4, -114, -11, -16
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -51, 42, 20, 31, -102, 11, -11, 16, 41, 64, 54, 35, 79, -51, 126, 98
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    uint64_t masked[] = {
    0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1
    };
    const uint64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4 (in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4 (in2, vl);
    vint16mf4_t out_v = __riscv_vle16_v_i16mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_i16mf4 (int16_t *out, vint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    71, 29, -47, -98, -39, 11, -11, 16, 41, 64, -82, 35, 4, -51, -11, 98
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
