/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    -101, -110, 17, -124, 26, 21, -78, -122, -108, 107, -30, -36, -76, -35, -122, -103
    };
    const int16_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4 (in1, vl);
    vint16m4_t out_v = __riscv_vle16_v_i16m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmv_v_v_i16m4 (src, vl);
        void __riscv_vse16_v_i16m4 (int16_t *out, vint16m4_t out_v, size_t vl);
        in1 += 2;
    int16_t golden[] = {
    -101, -110, 17, -124, 26, 21, -78, -122, -108, 107, -30, -36, -76, -35, -122, -103
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
