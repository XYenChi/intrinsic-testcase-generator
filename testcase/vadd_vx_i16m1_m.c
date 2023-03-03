/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    19146, 36401, 34850, 7377, 10018, 3637, 34549, 15873, 16357, 42461, 53215, 51801, 18024, 45119, 47527, 11714
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    41840, 62082, 12107, 26647, 37780, 23703, 16321, 21367, 24686, 39684, 26206, 24873, 1495, 54750, 54939, 20790
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    11130, 59223, 23854, 6838, 59036, 40743, 26593, 3547, 47033, 7729, 15767, 16102, 10492, 25296, 49150, 6680
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    11130, 59223, 23854, 34024, 59036, 40743, 26593, 3547, 47033, 82145, 79421, 76674, 10492, 99869, 49150, 6680
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
