/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1950926122, 4408246, 1851974777, 973971011, 1550739703, 3564170121, 3918047526, 758306311, 1162294050, 1920521818, 3636903662, 2237750892, 1035140487, 3234391538, 4234874239, 3796248301
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3426478350, 3113355068, 1784960144, 3025663758, 3102561682, 2563750086, 413983798, 2652749009, 3881030191, 2426632535, 1964370153, 2700270618, 216811395, 2143394263, 1364476304, 785426037
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    bool8_t masked[] = {
    1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vv_i32m4 (data1_v, data2_v, size_t vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3426478350, 4408246, 1784960144, 973971011, 1550739703, 3564170121, 413983798, 2652749009, 3881030191, 2426632535, 1964370153, 2237750892, 216811395, 2143394263, 1364476304, 3796248301
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
