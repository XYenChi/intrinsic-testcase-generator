/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    19669, 27483, 35392, 51592, 38434, 40679, 12115, 36161, 63942, 49333, 28061, 24051, 22717, 12522, 53867, 9231
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    52226, 19888, 50171, 7001, 44694, 12820, 51777, 15698, 23067, 32262, 26897, 13998, 15470, 9882, 22454, 14042
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m8(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m8_t data1_v = __riscv_vle16_v_i16m8 (*in1, vl);
    vint16m8_t data2_v = __riscv_vle16_v_i16m8 (*in2, size_t vl);
    vint16m8_t out_v = __riscv_vle16_v_i16m8 (*out, size_t vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16m8_t __riscv_vse16_v_i16 (int16m8_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    52226, 19888, 50171, 7001, 44694, 12820, 51777, 15698, 23067, 32262, 26897, 13998, 15470, 9882, 22454, 14042
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
