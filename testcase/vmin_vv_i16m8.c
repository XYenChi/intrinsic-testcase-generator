/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    76, -35, -32, -58, -59, -39, 81, -31, -118, -92, 23, -70, -119, -120, -83, 37
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    93, 52, -29, -114, -88, 100, 65, 75, -86, -98, -43, -88, -50, 20, 84, 48
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m8(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8 (in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8 (in2, vl);
    vint16m8_t out_v = __riscv_vle16_v_i16m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i16m8 (data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m8 (int16_t *out, vint16m8_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    93, 52, 65507, 65478, 65477, 100, 81, 75, 65450, 65444, 23, 65466, 65486, 20, 84, 48
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
