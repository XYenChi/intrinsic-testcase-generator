/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    45, 188, 156, 207, 3, 103, 203, 254, 229, 78, 133, 240, 136, 156, 119, 203
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    184, 98, 239, 73, 208, 20, 131, 104, 185, 216, 165, 56, 1, 244, 69, 109
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m4(size_t avl);
    const int out_data[] = {
    224, 75, 131, 230, 87, 198, 91, 210, 61, 205, 238, 126, 256, 51, 16, 147
    };
    const int8_t *out = &out_data[0];
    bool2_t masked[] = {
    1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0
    };
    const bool2_t *mask = &masked[0];
    vint8m4_t data1_v = __riscv_vle8_v_i8m4_m (mask, *in1, vl);
    vint8m4_t data2_v = __riscv_vle8_v_i8m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i8m4_m (mask, data1_v, data2_v, vl);
        void vint2_t __riscv_vse8m4_v_i8 (vbool8_t mask, int8m4_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    8280, 75, 37284, 15111, 624, 2060, 26593, 210, 42365, 205, 21945, 13440, 256, 51, 16, 147
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
