/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    20673, 31054, 64402, 9420, 27468, 36566, 51542, 36924, 9653, 30559, 57100, 6178, 15492, 24316, 25680, 11898
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    52642, 12328, 22841, 43100, 59424, 37527, 54680, 56593, 12291, 40035, 51021, 61110, 34946, 1801, 30903, 42717
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int out_data[] = {
    7992, 28740, 11721, 63168, 38314, 64163, 56470, 6849, 53577, 20440, 15386, 24573, 33475, 5392, 21662, 47186
    };
    const int16_t *out = &out_data[0];
    bool2_t masked[] = {
    0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1, 1, 0
    };
    const bool2_t *mask = &masked[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8_m (mask, *in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i16m8_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse16m8_v_i16 (vbool16_t mask, int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    7992, 43382, 11721, 52520, 86892, 74093, 56470, 93517, 53577, 20440, 108121, 67288, 33475, 26117, 56583, 47186
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
