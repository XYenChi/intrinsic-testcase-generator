/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    1124, 54203, 55092, 36149, 11077, 4786, 34401, 4203, 55495, 65064, 25031, 627, 25565, 9084, 61020, 9717
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    57355, 531, 41635, 11293, 43283, 826, 17336, 46694, 36731, 31530, 2388, 45049, 11378, 31714, 17435, 50650
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int out_data[] = {
    43408, 60527, 36477, 10445, 52117, 10613, 36517, 27403, 57490, 15397, 49410, 26993, 60682, 37358, 61831, 16102
    };
    const int16_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2_m (mask, *in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u16m2_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse16m2_v_i16 (vbool16_t mask, int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    43408, 53672, 13457, 24856, -32206, 3960, 17065, -42491, 18764, 33534, 49410, -44422, 14187, -22630, 61831, -40933
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
