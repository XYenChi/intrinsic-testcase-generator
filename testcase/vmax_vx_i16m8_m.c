/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    2361, 22595, 16186, 47282, 27528, 22577, 41696, 25778, 16531, 45279, 12585, 22745, 44911, 22305, 55070, 14598
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    9356, 49339, 31547, 30774, 63413, 2864, 10214, 4282, 14967, 5959, 45042, 31668, 21957, 54306, 44770, 25146
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    61151, 14434, 28362, 35408, 7093, 37640, 43209, 58878, 21229, 34255, 3851, 62818, 39243, 15512, 25670, 39647
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    9356, 14434, 31547, 35408, 63413, 37640, 41696, 58878, 16531, 45279, 45042, 31668, 44911, 54306, 55070, 39647
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
