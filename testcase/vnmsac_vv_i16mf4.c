/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    97, 33, -5, 68, -25, -7, -108, -98, 51, -50, 126, -29, -40, -46, 65, -44
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    38, -38, -114, 4, -52, 77, 41, -52, 2, 91, 119, 91, -118, -104, 117, -70
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4 (in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4 (in2, vl);
    vint16mf4_t out_v = __riscv_vle16_v_i16mf4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vv_i16mf4 (out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf4 (int16_t *out, vint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    61851, 1255, 64967, 65264, 64237, 539, 4429, 60440, 65435, 4551, 50542, 2640, 60816, 60752, 57932, 62457
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
