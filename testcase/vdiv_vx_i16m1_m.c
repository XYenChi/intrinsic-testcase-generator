/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    2564, 29293, 49689, 19237, 13598, 44866, 20637, 55573, 57560, 52421, 58996, 37442, 8016, 15814, 23302, 41810
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    24687, 31835, 51718, 17291, 9203, 7372, 58910, 54191, 57326, 58328, 50026, 57548, 28460, 13564, 59036, 39503
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    38204, 61045, 19566, 29400, 8611, 23589, 8722, 43201, 6257, 10683, 9592, 21736, 33251, 44404, 50019, 23872
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    9, 1, 1, 29400, 0, 23589, 2, 0, 6257, 1, 0, 1, 3, 0, 2, 23872
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
