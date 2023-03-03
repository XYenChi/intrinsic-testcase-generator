/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    11626, 40980, 17149, 56100, 16788, 17290, 5339, 45438, 33850, 4758, 36354, 33592, 40, 39414, 49165, 17948
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    29711, 11884, 60957, 11393, 32533, 40464, 43314, 16173, 35365, 56475, 51589, 59106, 21749, 55275, 27514, 18801
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    43395, 7322, 57268, 65410, 59140, 2473, 9201, 49393, 43057, 27019, 47376, 52528, 60798, 9339, 54330, 15995
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    43395, 11884, 60957, 11393, 59140, 40464, 43314, 16173, 43057, 56475, 51589, 52528, 60798, 9339, 54330, 15995
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
