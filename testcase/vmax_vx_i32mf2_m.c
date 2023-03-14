/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    24, 76, 44, 15, 55, -127, 29, -42, -43, 74, 85, 53, -61, -101, -125, 63
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    126, 100, -60, -93, 16, 71, -103, -66, 10, 81, -101, 22, -113, -91, -87, -114
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int out_data[] = {
    1, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1
    };
    const int32_t *out = &out_data[0];
    uint64_t masked[] = {
    0, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0
    };
    const uint64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i32mf2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32mf2 (bool32_t mask, int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1, 100, 44, 1, 55, 0, 29, 1, 0, 81, 85, 53, 4294967235, 1, 4294967209, 1
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
