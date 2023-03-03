/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    40681, 27317, 24286, 10804, 26656, 36786, 39866, 53481, 16054, 41422, 58988, 11204, 1788, 54684, 43565, 30051
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    54282, 45719, 48135, 22469, 43878, 56178, 14528, 25771, 30749, 6196, 17774, 49655, 4751, 35095, 21428, 56961
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    21569, 33457, 63094, 1975, 31038, 11695, 62417, 11149, 31068, 36092, 6246, 31144, 30776, 17019, 12075, 23837
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    21569, 33457, 63094, 242755076, 1169611968, 11695, 579173248, 1378258851, 31068, 36092, 6246, 556334620, 8494788, 1919134980, 12075, 1711735011
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
