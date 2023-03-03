/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    106, 114, 159, 198, 234, 185, 180, 11, 35, 31, 206, 149, 119, 83, 159, 35
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    251, 250, 252, 112, 130, 90, 132, 245, 217, 15, 212, 204, 35, 222, 75, 159
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m8(size_t avl);
    const int out_data[] = {
    237, 45, 5, 214, 206, 107, 5, 136, 156, 234, 141, 36, 22, 246, 196, 204
    };
    const int8_t *out = &out_data[0];
    bool1_t masked[] = {
    1, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0
    };
    const bool1_t *mask = &masked[0];
    vint8m8_t data1_v = __riscv_vle8_v_i8m8_m (mask, *in1, vl);
    vint8m8_t data2_v = __riscv_vle8_v_i8m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i8m8_m (mask, data1_v, data2_v, vl);
        void vint1_t __riscv_vse8m8_v_i8 (vbool8_t mask, int8m8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    26606, 45, 5, 22176, 30420, 107, 23760, 2695, 156, 234, 141, 36, 4165, 18426, 11925, 204
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
