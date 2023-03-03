/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    58986, 44158, 64797, 9007, 42250, 29459, 49348, 62871, 19503, 27428, 531, 61283, 46114, 41974, 36987, 50860
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    30735, 55001, 49534, 11234, 40223, 33002, 18435, 19429, 40060, 51166, 36865, 63453, 7819, 29031, 13961, 62560
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    38652, 44331, 35144, 16157, 21084, 3700, 13532, 26818, 40073, 51750, 53059, 2049, 52170, 4465, 7318, 47694
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    38652, 10843, 35144, 2227, 21084, 3700, 18435, 26818, 1054, 23738, 226, 2049, 7819, 29031, 13961, 11700
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
