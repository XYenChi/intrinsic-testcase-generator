/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    32554, 26073, 23291, 61581, 51620, 53801, 57867, 3949, 11937, 15549, 31484, 65264, 21831, 52779, 19165, 18693
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    61346, 18897, 35932, 54755, 27820, 15606, 2721, 52943, 1156, 50976, 31559, 63746, 22196, 2940, 35415, 5030
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    17962, 11975, 63022, 18814, 1238, 6292, 48317, 8379, 48734, 25542, 27301, 7267, 50020, 20876, 19278, 15469
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0
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
    93901, 44970, 59223, 116336, 79440, 69408, 60589, 56893, 13093, 66526, 63043, 129010, 44028, 55719, 54581, 23723
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
