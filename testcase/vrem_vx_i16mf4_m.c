/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    10001, 60966, 47150, 39823, 56809, 10979, 46544, 6945, 44392, 45074, 45436, 39406, 54096, 13497, 4382, 23753
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    14482, 45089, 40163, 14708, 9537, 15864, 49044, 62913, 53955, 57245, 58710, 18614, 59558, 4805, 47182, 49954
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    44039, 55616, 29866, 28106, 22569, 64289, 50268, 12261, 12071, 58792, 2742, 27260, 51394, 44656, 40732, 13386
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    4481, 45089, 40163, 28106, 9537, 64289, 2500, 408, 12071, 12171, 2742, 27260, 51394, 4805, 40732, 13386
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
