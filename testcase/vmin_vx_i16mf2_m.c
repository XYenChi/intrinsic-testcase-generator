/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    54846, 53288, 36640, 27561, 32609, 20455, 4858, 16646, 5475, 22135, 15154, 42675, 4879, 31416, 25263, 21788
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    8338, 46859, 42538, 53100, 62955, 51176, 51299, 16328, 31345, 5057, 14082, 44720, 8764, 54707, 42367, 25788
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    53732, 6412, 34324, 13888, 38108, 10574, 47460, 40668, 3241, 3421, 49775, 48546, 18054, 50988, 7207, 40098
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    53732, 53288, 34324, 53100, 38108, 10574, 51299, 16646, 31345, 3421, 15154, 44720, 8764, 50988, 42367, 25788
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
