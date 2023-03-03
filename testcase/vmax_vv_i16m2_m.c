/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    39452, 59056, 15563, 38279, 25198, 49293, 4806, 57271, 47112, 50517, 14, 10690, 32441, 22823, 17209, 54574
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    58478, 9725, 4479, 32030, 41207, 53900, 13732, 50956, 32038, 13934, 25503, 33617, 17961, 62033, 65336, 5841
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    11920, 62741, 11176, 47943, 54396, 46656, 65078, 11424, 60658, 18994, 34308, 36865, 3245, 58787, 14731, 63944
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    11920, 59056, 15563, 38279, 41207, 46656, 65078, 57271, 47112, 18994, 34308, 33617, 32441, 58787, 65336, 63944
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
