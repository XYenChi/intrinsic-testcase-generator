/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    29688, 18487, 13170, 28066, 29933, 5736, 59334, 41190, 32550, 58528, 61394, 54240, 54782, 53391, 38212, 7972
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    64464, 24613, 2399, 58420, 18767, 55584, 43996, 45260, 59035, 21258, 43978, 62458, 62941, 4041, 54443, 28933
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    10651, 30893, 32033, 35053, 3745, 12393, 20223, 49190, 44449, 15248, 29429, 19773, 63753, 37063, 9414, 36164
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    10651, 1, 32033, 35053, 3745, 9, 20223, 49190, 44449, 0, 0, 1, 1, 0, 9414, 3
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
