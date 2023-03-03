/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    46486, 22314, 50512, 4775, 20643, 30404, 58131, 12976, 43638, 3789, 25912, 14186, 43749, 4420, 62997, 43512
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    33899, 14862, 32568, 63668, 27277, 8421, 4726, 5032, 2325, 13670, 29794, 31898, 51654, 44712, 58663, 23215
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
        out_v = __riscv_vsub_vv_u16mf4 (data1_v, data2_v, vl);
        void vint16mf4_t __riscv_vse16_v_i16 (int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    12587, 7452, 17944, -58893, -6634, 21983, 53405, 7944, 41313, -9881, -3882, -17712, -7905, -40292, 4334, 20297
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
