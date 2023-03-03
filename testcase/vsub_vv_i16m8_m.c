/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    11094, 8218, 43929, 58015, 7740, 20675, 49504, 63072, 24843, 25538, 1068, 28760, 21748, 10837, 23823, 35392
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    38941, 7752, 52626, 60638, 17321, 3490, 324, 51975, 64439, 10577, 656, 6635, 7435, 1872, 1750, 24372
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    60075, 51760, 29148, 19065, 49895, 59818, 56876, 17846, 18449, 65265, 45145, 35789, 30757, 5665, 8836, 12808
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    60075, 51760, -8697, -2623, 49895, 17185, 56876, 11097, -39596, 14961, 412, 22125, 30757, 5665, 22073, 11020
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
