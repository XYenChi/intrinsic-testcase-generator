/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    37410, 3973, 56713, 5279, 26190, 1133, 38382, 54405, 47076, 45885, 17367, 39694, 22988, 3244, 46008, 18172
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    17360, 46054, 56092, 3192, 42833, 1293, 36859, 9632, 7782, 20037, 42844, 35699, 53605, 21174, 4633, 53778
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    16969, 64288, 61636, 51270, 46820, 5694, 55811, 35333, 64283, 12753, 48155, 50384, 53214, 48516, 36825, 60695
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    16969, 64288, 56092, 51270, 46820, 160, 55811, 9632, 7782, 12753, 48155, 50384, 53214, 1710, 36825, 17434
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
