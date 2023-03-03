/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    11134, 10787, 746, 46254, 50702, 44513, 12834, 10486, 32285, 34252, 29564, 37600, 14862, 56521, 12998, 29687
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    6468, 46178, 14608, 38631, 27513, 110, 8096, 25742, 14316, 45214, 6727, 1120, 55583, 14418, 25564, 32300
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    56641, 45435, 55134, 3233, 39342, 4736, 56997, 14442, 21972, 20122, 47689, 49239, 56791, 53627, 49382, 29506
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    17603, 56966, 15354, 84885, 78215, 44623, 20930, 36228, 46602, 79467, 36292, 38720, 70445, 70939, 38563, 61988
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
