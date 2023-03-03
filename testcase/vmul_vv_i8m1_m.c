/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    133, 30, 200, 88, 29, 88, 21, 160, 30, 168, 181, 60, 179, 54, 221, 124
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    256, 89, 225, 54, 204, 164, 164, 118, 154, 160, 65, 205, 106, 22, 60, 140
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8m1(size_t avl);
    const int out_data[] = {
    126, 136, 141, 72, 139, 103, 33, 155, 250, 196, 216, 24, 205, 15, 234, 107
    };
    const int8_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint8m1_t data1_v = __riscv_vle8_v_i8m1_m (mask, *in1, vl);
    vint8m1_t data2_v = __riscv_vle8_v_i8m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i8m1_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse8m1_v_i8 (vbool8_t mask, int8m1_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    126, 136, 45000, 4752, 139, 14432, 33, 18880, 250, 196, 216, 12300, 205, 1188, 13260, 17360
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
