/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    22608, 42854, 1492, 19926, 39338, 25597, 63725, 37750, 3773, 56574, 49826, 40817, 18089, 58245, 4668, 61950
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    35727, 58156, 57518, 29329, 7015, 53440, 6603, 41537, 36760, 19005, 36371, 54661, 1249, 49611, 19843, 35339
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    8710, 17144, 21654, 41424, 60915, 7997, 30052, 62592, 36100, 62278, 45612, 14697, 25078, 7532, 56298, 55099
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    35727, 17144, 21654, 29329, 7015, 7997, 30052, 41537, 36100, 62278, 45612, 14697, 25078, 49611, 56298, 55099
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
