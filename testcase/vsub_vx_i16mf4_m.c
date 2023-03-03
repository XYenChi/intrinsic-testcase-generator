/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    55167, 38807, 40771, 5537, 60879, 19579, 32675, 22859, 21670, 40741, 30478, 65231, 49797, 19271, 54513, 48049
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    16726, 28541, 40105, 25835, 5228, 11395, 55909, 18332, 55687, 24083, 34624, 45755, 49572, 51401, 15870, 6021
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    1840, 30388, 24708, 23273, 57542, 20473, 10948, 4899, 19772, 9014, 31302, 27248, 27704, 58840, 13786, 56771
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    38441, 30388, 24708, 23273, 57542, 8184, 10948, 4527, -34017, 16658, -4146, 27248, 225, -32130, 38643, 56771
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
