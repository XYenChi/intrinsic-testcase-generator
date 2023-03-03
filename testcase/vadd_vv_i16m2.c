/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    55778, 50514, 44297, 30656, 50563, 51832, 50268, 55946, 31903, 60798, 1623, 11706, 6309, 51556, 47826, 16373
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    40946, 45219, 30408, 49220, 19299, 9124, 43325, 46934, 43568, 29403, 63200, 33217, 13885, 9158, 60879, 9138
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2 (*in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2 (*in2, vl);
    vint16m2_t out_v = __riscv_vle16_v_i16m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i16m2 (data1_v, data2_v, vl);
        void vint16m2_t __riscv_vse16_v_i16 (int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    96724, 95733, 74705, 79876, 69862, 60956, 93593, 102880, 75471, 90201, 64823, 44923, 20194, 60714, 108705, 25511
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
