/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    49925, 57545, 32701, 27254, 25377, 51643, 40364, 44943, 61361, 51729, 12093, 4784, 23024, 5053, 12494, 60585
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    47707, 30332, 64327, 49848, 6762, 63857, 49177, 52367, 3680, 36670, 56614, 12475, 64764, 12975, 43676, 49565
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    46780, 39571, 46602, 45061, 53587, 59875, 34421, 12289, 16689, 18341, 8456, 65532, 59049, 11242, 36279, 46498
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    0, 39571, 46602, 1, 53587, 1, 1, 12289, 0, 18341, 4, 65532, 59049, 2, 36279, 0
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
