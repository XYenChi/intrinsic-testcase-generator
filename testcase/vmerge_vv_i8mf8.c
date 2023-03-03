/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int8_t data1[] = {
    186, 12, 222, 126, 31, 208, 106, 4, 67, 69, 78, 168, 244, 239, 213, 62
    };
    const int8_t *in1 = &data1[0];
    const int8_t data2[] = {
    72, 178, 256, 94, 241, 81, 94, 237, 238, 46, 4, 55, 122, 209, 213, 95
    };
    const int8_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e8mf8(size_t avl);
    bool64_t masked[] = {
    1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint8mf8_t data1_v = __riscv_vle8_v_i8mf8 (mask, *in1, vl);
    vint8mf8_t data2_v = __riscv_vle8_v_i8mf8 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vv_i8mf8 (data1_v, data2_v, size_t vl);
        void vint64_t __riscv_vse8mf8_v_i8 (vbool8_t mask, int8mf8_t *out, out_v, size_t vl);
        in1 += 1;
        in2 += 1;
        out += 1;
        mask += 1;
      }
    int8_t golden[] = {
    72, 12, 222, 126, 31, 208, 94, 4, 238, 46, 78, 168, 122, 209, 213, 95
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
