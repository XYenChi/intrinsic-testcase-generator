/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    145, 208, 87, 90, 211, 12, 245, 80, 141, 197, 63, 197, 198, 80, 86, 71
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    181, 13, 83, 91, 252, 42, 250, 47, 249, 214, 82, 28, 181, 42, 192, 1
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf2(size_t avl);
    const int out_data[] = {
    151, 0, 189, 168, 136, 36, 249, 11, 225, 3, 216, 114, 203, 161, 209, 88
    };
    const int8_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint8mf2_t data1_v = __riscv_vle8_v_i8mf2_m (mask, *in1, vl);
    vint8mf2_t data2_v = __riscv_vle8_v_i8mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i8mf2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse8mf2_v_i8 (vbool8_t mask, int8mf2_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -37, 195, 4, -2, -41, -31, -5, 32, -109, -18, -19, 169, 17, 37, -106, 69
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
