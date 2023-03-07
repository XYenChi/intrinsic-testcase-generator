/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1425691166, -546884851, -125974699, -1224356699, -1517586513, 2036235963, -1227176276, -1008952060, 1284371956, 800093312, -976066102, 413867156, -2014139441, 416991613, -761310271, 476589197
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -1257020647, -799110839, -640577606, -1185859256, 1126045245, 922427872, -716930064, 726802641, 769920879, -576963869, 786541430, -1733773168, -1078018033, -1019067900, 322629510, 6391328
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vx_i32m1 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m1 (int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1994505916, -302885524, -828055618, -2479680322, 264141507, 2057445163, 245441643, -876512151, 2563305519, 1494553117, -2159191134, 1971701884, -3202341559, 681977151, 1318794542, 2219174062
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
