/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -228355292, 280967772, -307442595, -236840053, -640664171, 1879244140, -1461303020, 1418389395, 1326239960, 281817320, -1047303139, -1407797967, 714175715, 526606228, -1911190791, 74783495
    };
    const int32_t *in1 = &data1[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    const int out_data[] = {
    -195090693, -849075018, -267084640, 774583538, -314090065, -1369490960, -496402453, 1550127170, -1645284026, -455924498, 1570770293, 875078004, 163040454, -997408669, -896993441, -117589206
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, in1, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vneg_v_32m1 (mask, data1_v, vl);
        void __riscv_vse32_v_i32m1 (bool32_t mask, int32_t *out, vint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    228355292, -280967772, 307442595, 236840053, 640664171, -1879244140, 1461303020, -1418389395, -1326239960, -281817320, 1047303139, 1407797967, -714175715, -526606228, 1911190791, -74783495
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
