/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    15691, 15167, 40291, 62781, 61137, 2267, 32526, 42954, 2267, 15089, 52718, 60768, 56879, 39813, 8724, 49176
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    21883, 53983, 59448, 52058, 35984, 62618, 25328, 20697, 6248, 51255, 53144, 62579, 20781, 35252, 10739, 24244
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    54341, 62598, 13610, 61651, 61909, 19858, 9331, 407, 51803, 6508, 56560, 13243, 64026, 18885, 27199, 56655
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vv_i16mf2_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    54341, 62598, 13610, 61651, 0, 19858, 0, 0, 2, 3, 56560, 1, 0, 0, 27199, 56655
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
