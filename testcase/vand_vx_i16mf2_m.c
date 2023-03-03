/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    9048, 42948, 20015, 49286, 8246, 63366, 8114, 7428, 35851, 54615, 41107, 3865, 47372, 40624, 38799, 35094
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    35791, 41852, 9158, 61955, 63941, 35797, 48640, 21063, 16834, 38205, 38468, 61407, 31115, 52587, 46129, 6989
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    34359, 62603, 59162, 39342, 38374, 25393, 2234, 34955, 31895, 56645, 58085, 16296, 60923, 12641, 393, 36091
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    35791, 41852, 9158, 39342, 63941, 25393, 48640, 34955, 16834, 56645, 38468, 16296, 60923, 12641, 46129, 36091
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
