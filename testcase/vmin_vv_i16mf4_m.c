/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    33372, 24611, 20005, 12227, 45317, 17632, 5559, 29651, 53554, 57472, 10180, 56304, 4934, 37324, 48564, 49771
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    40109, 34699, 1624, 46113, 56644, 37495, 40443, 2721, 30306, 2508, 27570, 32119, 27792, 49398, 5132, 38504
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    14999, 25401, 31610, 18461, 6140, 23697, 63818, 57077, 2846, 33252, 36815, 24699, 3914, 7670, 58220, 111
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    14999, 25401, 20005, 18461, 6140, 37495, 63818, 57077, 2846, 33252, 27570, 24699, 3914, 7670, 58220, 111
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
