/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    22189, 14385, 41786, 25773, 27828, 19817, 12589, 26882, 39285, 53935, 64428, 303, 12341, 35279, 23779, 53986
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    32938, 7332, 18619, 20715, 7055, 54365, 55178, 29540, 64864, 8317, 52008, 58316, 22222, 53670, 46077, 22735
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4 (*in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4 (*in2, vl);
    vint16mf4_t out_v = __riscv_vle16_v_i16mf4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u16mf4 (data1_v, data2_v, vl);
        void vint16mf4_t __riscv_vse16_v_i16 (int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    -10749, 7053, 23167, 5058, 20773, -34548, -42589, -2658, -25579, 45618, 12420, -58013, -9881, -18391, -22298, 31251
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
