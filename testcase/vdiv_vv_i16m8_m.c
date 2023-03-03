/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    36897, 8569, 59319, 28653, 4573, 42590, 50541, 12980, 59816, 7249, 13943, 50586, 13330, 14041, 20946, 33696
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    38217, 64161, 14969, 26020, 4812, 52713, 38578, 48357, 45940, 20932, 39343, 862, 49988, 60459, 4038, 14726
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    14210, 32930, 9616, 30014, 63717, 59267, 19718, 35394, 45007, 59633, 31602, 39924, 36310, 24098, 34091, 21415
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 0
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vv_i16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    1, 32930, 0, 30014, 1, 59267, 0, 35394, 0, 59633, 2, 39924, 36310, 4, 0, 21415
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
