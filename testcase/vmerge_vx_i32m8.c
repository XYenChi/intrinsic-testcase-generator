/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4099059537, 1183095079, 2503759888, 1582000698, 1971693002, 791341116, 281999929, 931368062, 1249818730, 4012714251, 313039647, 421168732, 3665125072, 2850515692, 3102101381, 1506515870
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3316770517, 2218200935, 1224413466, 3654459513, 2773157312, 1084432617, 3715454524, 2679244598, 2870689286, 762373403, 1442736211, 1124947992, 1947908686, 758364290, 1776343647, 1686180472
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    bool4_t masked[] = {
    0, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmerge_vx_i32m8 (data1_v, data2_v, size_t vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    4099059537, 2218200935, 2503759888, 1582000698, 2773157312, 1084432617, 3715454524, 931368062, 2870689286, 762373403, 1442736211, 1124947992, 1947908686, 758364290, 3102101381, 1686180472
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
