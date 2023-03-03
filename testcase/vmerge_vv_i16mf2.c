/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    16879, 49786, 41749, 22662, 65469, 28237, 8755, 53503, 62790, 55173, 48263, 22203, 50498, 2086, 63032, 4107
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    40783, 17010, 72, 64990, 51805, 47879, 40395, 26229, 51365, 14058, 24415, 49340, 8741, 59952, 64877, 11910
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    bool32_t masked[] = {
    1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2 (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vv_i16mf2 (data1_v, data2_v, size_t vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    40783, 17010, 41749, 22662, 65469, 47879, 8755, 53503, 62790, 14058, 48263, 49340, 50498, 59952, 63032, 11910
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
