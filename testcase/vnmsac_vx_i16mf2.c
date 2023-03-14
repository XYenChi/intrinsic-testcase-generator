/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    101, -123, 75, 109, -45, -103, 8, -42, 38, -35, -117, -36, 69, -15, 61, -64
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -49, -71, 72, -128, -89, 89, -114, 75, -122, -45, -3, -114, 114, -70, -97, -127
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2 (in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2 (in2, vl);
    vint16mf2_t out_v = __riscv_vle16_v_i16mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vx_i16mf2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf2 (int16_t *out, vint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    4949, 56803, 60136, 13953, 61531, 9168, 912, 3150, 4637, 63961, 65185, 61432, 57671, 64486, 5918, 57409
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
