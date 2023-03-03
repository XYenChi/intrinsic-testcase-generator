/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    14241, 53305, 9864, 37284, 44076, 28876, 48330, 23170, 64120, 9416, 53659, 27779, 21854, 6875, 31433, 22407
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    51289, 23822, 16056, 38619, 23147, 44948, 22733, 63957, 29756, 56165, 53736, 47888, 27609, 7633, 11981, 57735
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    63413, 42769, 14391, 8537, 28679, 16864, 45616, 51835, 9062, 19893, 57046, 58144, 63758, 33815, 37583, 41674
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    63413, 23822, 16056, 8537, 28679, 16864, 22733, 51835, 9062, 56165, 57046, 47888, 27609, 7633, 37583, 57735
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
