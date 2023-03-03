/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    34974, 40990, 55631, 63821, 23346, 18922, 24909, 11159, 24907, 17228, 18708, 31538, 17053, 21273, 15066, 63505
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    28656, 54769, 4937, 61469, 63557, 56783, 16031, 46509, 52145, 42368, 21073, 42636, 12795, 21860, 57526, 14383
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    52589, 35096, 7498, 14088, 52979, 53806, 4956, 17079, 27433, 29850, 15547, 57861, 7075, 18696, 26671, 13014
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    52589, 54769, 7498, 14088, 63557, 53806, 16031, 46509, 52145, 42368, 15547, 42636, 12795, 18696, 57526, 14383
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
