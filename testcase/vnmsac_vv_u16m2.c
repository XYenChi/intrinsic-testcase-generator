/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    75, 248, 180, 191, 69, 3, 81, 65, 180, 58, 199, 161, 149, 73, 210, 180
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    246, 128, 211, 150, 39, 204, 95, 19, 218, 135, 131, 68, 248, 26, 95, 82
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16m2_t data1_v = __riscv_vle16_v_u16m2 (in1, vl);
    vuint16m2_t data2_v = __riscv_vle16_v_u16m2 (in2, vl);
    vuint16m2_t out_v = __riscv_vle16_v_u16m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vv_u16m2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse16_v_u16m2 (uint16_t *out, vuint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    47086, 33792, 27556, 36886, 62846, 64925, 57842, 64301, 26296, 57707, 39467, 54589, 28584, 63638, 45586, 50777
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