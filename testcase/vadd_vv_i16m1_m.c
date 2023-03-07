/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    9365, 24492, 21638, -4146, -32538, -2081, 14090, 20224, -29805, 20366, -14012, -5510, 18900, 15149, -31564, -19693
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -12340, -9244, -3971, -17395, -25113, 435, -20117, -21753, -30216, -3761, 27497, 9848, 1780, 32610, -28420, 3939
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m1(avl);
    const int out_data[] = {
    25236, 27122, 2547, 16615, -26524, -28339, -4264, -18290, 10856, -28543, -26661, -8900, 32158, -803, -17308, 5463
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i16m1_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m1 (bool16_t mask, int16_t *out, vint16m1_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    25237, 27123, 2548, 16616, -26524, -28338, -4263, -18289, 10857, -28542, -26661, -8899, 32159, -803, -17307, 5464
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
