/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    47314, 2323, 5538, 41858, 18376, 33118, 59031, 32449, 26734, 61337, 23822, 18518, 29010, 44993, 15599, 22649
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    37068, 4076, 65284, 48394, 29146, 4332, 39275, 62919, 8478, 23338, 16534, 39932, 28807, 33947, 58075, 32934
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    41855, 10547, 48474, 47750, 39216, 28327, 56165, 36436, 33558, 5823, 7553, 63894, 27650, 26010, 36580, 10646
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    84382, 6400, 70822, 90253, 47522, 37451, 98307, 95369, 35212, 84675, 40356, 58451, 57818, 78941, 73675, 55584
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
