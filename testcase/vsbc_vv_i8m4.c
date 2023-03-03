/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    53, 235, 109, 12, 245, 62, 183, 95, 18, 170, 156, 44, 133, 171, 224, 225
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    207, 197, 16, 27, 140, 177, 229, 215, 136, 32, 52, 105, 138, 94, 0, 20
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m4(size_t avl);
    const int8_t out_data[16];
    const int8_t *out = &out_data[0];
    vint8m4_t data1_v = __riscv_vle8_v_i8m4 (*in1, vl);
    vint8m4_t data2_v = __riscv_vle8_v_i8m4 (*in2, vl);
    vint8m4_t out_v = __riscv_vle8_v_i8m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i8m4 (data1_v, data2_v, vl);
        void vint8m4_t __riscv_vse8_v_i8 (int8m4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
      }
    int8_t golden[] = {
    -154, 38, 93, -15, 105, -115, -46, -120, -118, 138, 104, -61, -5, 77, 224, 205
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
