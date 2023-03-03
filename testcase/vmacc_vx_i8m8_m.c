/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    48, 107, 216, 203, 61, 30, 181, 31, 77, 161, 86, 38, 193, 73, 55, 38
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    52, 105, 152, 112, 145, 228, 130, 135, 177, 78, 18, 206, 78, 44, 183, 241
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m8(size_t avl);
    const int out_data[] = {
    186, 88, 138, 40, 250, 120, 170, 225, 111, 122, 25, 94, 153, 92, 86, 217
    };
    const int8_t *out = &out_data[0];
    bool1_t masked[] = {
    1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0
    };
    const bool1_t *mask = &masked[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8_m (mask, *in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i8m8_m (mask, data1_v, data2_v, vl);
        void vint1_t __riscv_vse8m8_v_i8 (vbool8_t mask, int8m8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    8929, 9416, 29808, 8120, 15251, 3600, 30770, 6976, 8547, 19643, 2151, 3572, 29529, 6717, 4730, 8246
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
