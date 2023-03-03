/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    36009, 12178, 7100, 24357, 24109, 20324, 7088, 52110, 48024, 21035, 35533, 26117, 17668, 32921, 42945, 15940
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    53481, 37228, 39527, 40316, 15826, 17189, 56579, 24305, 59568, 11720, 39986, 50093, 58558, 29553, 18376, 43327
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    15316, 12373, 52026, 62102, 64930, 41371, 1997, 22542, 52455, 1205, 9253, 19162, 15916, 56895, 4715, 51617
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    15316, 12373, -32427, -15959, 64930, 3135, -49491, 27805, -11544, 1205, -4453, -23976, 15916, 56895, 4715, -27387
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
