/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    14311, 42039, 1266, 63222, 37970, 4106, 53624, 28489, 6518, 65511, 47021, 41678, 62710, 59052, 57595, 60992
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    20260, 53360, 35991, 9271, 58795, 38216, 61222, 42303, 3831, 21634, 21508, 50057, 54895, 40637, 65448, 25680
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf2(size_t avl);
    const int out_data[] = {
    35571, 23503, 38347, 29984, 46486, 7598, 6469, 3656, 54387, 11218, 53209, 56512, 44283, 26392, 24436, 36720
    };
    const int16_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2_m (mask, *in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32_t __riscv_vse16mf2_v_i16 (vbool16_t mask, int16mf2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    34571, 95399, 37258, 72493, 96765, 42323, 114846, 70793, 10350, 87145, 68530, 91735, 117606, 99689, 123043, 86672
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
