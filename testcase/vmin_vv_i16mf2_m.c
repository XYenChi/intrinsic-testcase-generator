/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    60358, 22794, 9782, 61247, 49825, 65214, 7980, 42967, 4, 14213, 43014, 52310, 48512, 46276, 6543, 13458
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    54869, 8433, 34769, 18849, 2570, 32535, 38510, 65328, 52397, 41498, 22551, 61795, 17237, 21268, 24431, 50601
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    11952, 49805, 43586, 27199, 61083, 56352, 33550, 21303, 50132, 7493, 60060, 14543, 32067, 29099, 59243, 7001
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    11952, 22794, 43586, 27199, 49825, 65214, 33550, 65328, 50132, 7493, 60060, 61795, 32067, 29099, 59243, 50601
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
