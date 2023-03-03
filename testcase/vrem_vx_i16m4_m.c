/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    18564, 35299, 2314, 5205, 1383, 28368, 31485, 48757, 12315, 15139, 65349, 49797, 46208, 34816, 21726, 38129
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    33221, 39959, 47926, 33697, 58241, 44151, 3326, 13806, 40628, 22980, 58569, 27298, 13952, 21288, 58253, 37911
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m4(size_t avl);
    const int out_data[] = {
    54155, 25555, 26310, 3408, 54545, 33937, 33246, 19370, 55513, 32523, 38048, 19755, 1961, 59643, 26414, 41692
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i16m4_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse16m4_v_i16 (vbool16_t mask, int16m4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    14657, 25555, 1646, 3408, 155, 15783, 3326, 13806, 55513, 7841, 58569, 27298, 13952, 59643, 14801, 37911
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
