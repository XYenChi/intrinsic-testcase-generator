/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    96, 126, 163, 251, 200, 23, 34, 15, 175, 139, 99, 0, 226, 62, 24, 196
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    49, 218, 154, 152, 5, 27, 121, 253, 50, 62, 100, 140, 50, 238, 186, 120
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf4(size_t avl);
    const int out_data[] = {
    172, 84, 220, 76, 106, 79, 174, 109, 215, 190, 43, 242, 72, 153, 116, 173
    };
    const int8_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1
    };
    const bool32_t *mask = &masked[0];
    vint8mf4_t data1_v = __riscv_vle8_v_i8mf4_m (mask, *in1, vl);
    vint8mf4_t data2_v = __riscv_vle8_v_i8mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i8mf4_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse8mf4_v_i8 (vbool8_t mask, int8mf4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    49, 92, 154, 76, 5, 79, 19, 13, 50, 190, 1, 242, 72, 153, 18, 120
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
