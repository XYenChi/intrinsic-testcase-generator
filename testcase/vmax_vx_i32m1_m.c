/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3275637691, 311836770, 1740008423, 185239000, 2313971437, 4196714090, 73259236, 3155527410, 1560615913, 2874404541, 2205448365, 3721854765, 213456578, 2986245409, 3509873435, 3387369189
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2051325409, 375000689, 1812532300, 459532366, 2077484232, 3053892222, 1565700042, 2835746271, 1593658797, 951892313, 2171682594, 2122501737, 2462715010, 2703441850, 526935335, 504395357
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    1770260591, 647725595, 1985336874, 2162788562, 4139655237, 1403691514, 477716524, 3567386975, 4187055588, 1983835587, 1435172302, 2161260376, 3522357538, 2965040370, 1862883355, 2495627801
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    1, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3275637691, 375000689, 1812532300, 459532366, 2313971437, 1403691514, 1565700042, 3155527410, 4187055588, 1983835587, 2205448365, 3721854765, 3522357538, 2965040370, 1862883355, 3387369189
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
