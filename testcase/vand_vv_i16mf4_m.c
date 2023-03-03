/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    17910, 18205, 17902, 7576, 31416, 56657, 40772, 5985, 41555, 51949, 48431, 50295, 47980, 65411, 37132, 49241
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    15611, 26749, 61646, 54271, 58046, 61427, 21892, 18877, 12717, 64332, 13459, 23180, 48387, 9673, 33976, 40969
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    29652, 2028, 61234, 25883, 48085, 4979, 22939, 30100, 1667, 42543, 5097, 49481, 33308, 6881, 50984, 65404
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1
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
    15611, 26749, 61234, 54271, 58046, 61427, 22939, 30100, 1667, 64332, 5097, 23180, 48387, 6881, 50984, 40969
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
