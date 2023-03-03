/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1887604622, 3241071637, 2928517041, 1384099604, 4188156256, 4006804588, 2128410833, 3975637441, 509069038, 3145848607, 439430641, 1275926454, 1305608481, 1111003466, 2800261016, 220213190
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3745330659, 2371681204, 810300082, 2228228516, 1951156054, 2046303899, 3923611866, 2642190842, 3734965010, 1172634877, 1683220451, 4255776046, 366964202, 1310371680, 3890537371, 3096665720
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i32m1 (data1_v, data2_v, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    7069703462846705898, 7686788682290410948, 2372977598460697362, 3084090206617107664, 8171746433992373824, 8199139850955488612, 8351058000081744378, 10504392837722515322, 1901355044604360380, 3688931794330066339, 739658641727239091, 5430057239390920884, 479111574354597162, 1455827478228242880, 10894520131302428936, 681926636564846800
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
