/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    6, 51, 197, 159, 8, 220, 66, 115, 77, 156, 25, 96, 24, 247, 219, 74
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    183, 160, 115, 52, 116, 21, 2, 151, 244, 225, 250, 256, 22, 134, 51, 244
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf4(size_t avl);
    const int out_data[] = {
    8, 2, 164, 111, 214, 79, 129, 132, 189, 237, 108, 88, 100, 148, 134, 66
    };
    const int8_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4_m (mask, *in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vx_i8mf4_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse8mf4_v_i8 (vbool8_t mask, int8mf4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    -178, -110, 82, 107, -108, 199, 64, -37, -168, -69, -226, -161, 2, 113, 168, -170
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
