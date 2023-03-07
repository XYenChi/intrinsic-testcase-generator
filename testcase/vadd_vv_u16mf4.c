/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    16390, 241, 27233, 2659, -23010, -21051, 23031, -21409, 27016, -25975, 12208, -23836, -2627, -22347, 5762, 2944
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    13826, -20824, 1315, -21186, -10522, -3686, -19218, -13394, 29304, 16496, -30318, -19174, 24012, 19517, 6855, 14145
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf4(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4 (*in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4 (*in2, vl);
    vint16mf4_t out_v = __riscv_vle16_v_i16mf4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u16mf4 (data1_v, data2_v, vl);
        void __riscv_vse16_v_i16mf4 (int16_t *out, vint16mf4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    23025, 350, 2713, -21223, -13151, -48801, 29602, -3842, 29210, -9479, 24371, -45343, -21301, -32277, 19908, 11651
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
