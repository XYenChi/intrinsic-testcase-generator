/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    3617, 37149, 58733, 12004, 52054, 36047, 22065, 51888, 37507, 40103, 53159, 65283, 28156, 56628, 56383, 7175
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    24391, 42823, 29418, 41980, 16055, 63297, 55650, 37145, 30708, 27019, 56147, 61443, 64395, 7631, 56079, 29137
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    60202, 49003, 39085, 26952, 11305, 19997, 9915, 26601, 1295, 5798, 13769, 62318, 56734, 63797, 9010, 13232
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    28009, 79973, 88152, 53984, 68109, 99345, 77716, 89033, 68215, 67123, 109307, 126726, 92552, 64260, 112462, 36313
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
