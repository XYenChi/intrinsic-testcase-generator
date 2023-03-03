/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    17067, 51856, 22728, 33784, 54395, 36099, 62633, 17861, 58744, 34797, 43903, 12139, 28073, 53639, 685, 48738
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    60920, 65409, 10917, 22197, 14856, 8928, 44431, 6777, 9568, 7972, 271, 39089, 19003, 36083, 57713, 17360
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    15505, 3533, 56971, 36794, 978, 20163, 49654, 63760, 32611, 27338, 42727, 42442, 11065, 59117, 59000, 23977
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    15505, 3533, 56971, 36794, 978, 45027, 49654, 63760, 68312, 27338, 42727, 42442, 11065, 59117, 59000, 66098
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
