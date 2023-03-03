/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    61, 223, 115, 168, 220, 123, 118, 120, 71, 126, 244, 210, 30, 86, 157, 194
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    237, 182, 65, 111, 242, 65, 7, 252, 193, 248, 217, 63, 67, 89, 167, 93
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m8(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8 (*in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8 (*in2, vl);
    vint8m8_t out_v = __riscv_vle8_v_i8m8 (*out, vl);
    const int out_data[] = {
    33, 170, 253, 139, 116, 39, 209, 36, 101, 95, 135, 51, 16, 64, 235, 206
    };
    const int8_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vv_i8m8 (data1_v, data2_v, vl);
        void vint8m8_t __riscv_vse8_v_i8 (int8m8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    14490, 40756, 7728, 18787, 53356, 8034, 1035, 30276, 13804, 31343, 53083, 13281, 2026, 7718, 26454, 18248
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
