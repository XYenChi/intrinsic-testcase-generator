/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    10362759, 2430950833, 3983446892, 175562361, 4007255618, 1907990490, 3280096309, 12303809, 1638033143, 2481990948, 488314904, 4273520801, 3881998325, 1510397477, 383488610, 121913080
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    4088087732, 3894028084, 2742399552, 2950444694, 3086839442, 3328403252, 466626426, 4230659529, 361741280, 468070845, 2368017741, 1272221124, 619341188, 2900995963, 2212340578, 2777750463
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    bool4_t masked[] = {
    1, 1, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vuint32m8_t data1_v = __riscv_vle32_v_u32m8 (in1, vl);
    vuint32m8_t data2_v = __riscv_vle32_v_i32m8 (in2, vl);
    vuint32m8_t out_v = __riscv_vle32_v_u32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m8 (uint32_t *out, vuint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    4088087732, 3894028084, 3983446892, 2950444694, 4007255618, 3328403252, 466626426, 4230659529, 361741280, 2481990948, 2368017741, 1272221124, 3881998325, 2900995963, 383488610, 121913080
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
