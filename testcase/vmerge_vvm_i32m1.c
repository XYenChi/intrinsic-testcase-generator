/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -494962044, 2117895606, 344267004, -2083886414, 6818890, 1950248167, 1604240452, -724562263, 1171932435, -85552790, 2027880560, 727503098, 386426414, 390747044, 854603105, 1597643670
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -974846294, 1590075889, -259833250, 2106616684, 665726047, -1046525779, -76783654, 654087021, -1641630312, 1562606298, -684477498, -912101596, 1013976937, -567401311, -1778983405, 699881673
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    bool32_t masked[] = {
    0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m1 (int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -494962044, 1590075889, -259833250, -2083886414, 665726047, 1950248167, 1604240452, -724562263, 1171932435, -85552790, -684477498, 727503098, 386426414, 390747044, -1778983405, 1597643670
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
