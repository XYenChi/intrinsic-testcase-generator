/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    3128, 59600, 45857, 49277, 12416, 40434, 43138, 15577, 12221, 59651, 55345, 6622, 59693, 10821, 60416, 5554
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    50951, 6294, 25330, 192, 33124, 610, 33354, 11669, 2714, 25555, 10483, 29298, 57022, 61442, 51498, 63652
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    17851, 58515, 8498, 23432, 65010, 59407, 7521, 41427, 9235, 32584, 45468, 23885, 15175, 61574, 38030, 6103
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    17851, 53306, 20527, 23432, -20708, 59407, 7521, 3908, 9235, 34096, 45468, 23885, 2671, -50621, 38030, 6103
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
