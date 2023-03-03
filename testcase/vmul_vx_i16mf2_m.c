/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    10157, 15383, 19520, 41723, 1631, 7498, 62187, 22491, 16272, 27033, 17349, 19552, 54956, 32935, 58021, 20928
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    10121, 64746, 33125, 52568, 52783, 40410, 43956, 48597, 2329, 9793, 40592, 15640, 6512, 34089, 45317, 6476
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    35913, 28065, 37469, 49982, 13039, 15014, 62964, 29150, 38343, 52958, 38495, 49614, 13172, 13000, 46527, 5773
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    35913, 28065, 646600000, 49982, 13039, 15014, 62964, 29150, 38343, 264734169, 38495, 305793280, 13172, 1122721215, 2629337657, 5773
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
