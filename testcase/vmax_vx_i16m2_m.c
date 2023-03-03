/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    41062, 40802, 23113, 483, 40364, 18270, 40813, 62793, 28771, 55900, 36103, 11711, 13685, 7433, 45236, 29309
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    54097, 60193, 38015, 13186, 154, 8588, 52680, 11755, 12133, 13393, 56933, 2252, 19930, 4258, 3789, 57939
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    41199, 36231, 43716, 9972, 7140, 16355, 36224, 26003, 61299, 48861, 57684, 38326, 56042, 31541, 22541, 51260
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    54097, 36231, 38015, 13186, 7140, 16355, 52680, 26003, 61299, 48861, 57684, 38326, 56042, 7433, 45236, 57939
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
