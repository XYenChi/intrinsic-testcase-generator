/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    211, 101, 95, 250, 131, 254, 150, 104, 241, 19, 30, 218, 161, 143, 97, 13
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    201, 46, 143, 184, 29, 15, 212, 51, 76, 19, 102, 145, 17, 114, 158, 240
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const uint64_t out_data[16];
    const uint64_t *out = &out_data[0];
    vuint64m8_t data1_v = __riscv_vle64_v_u64m8 (in1, vl);
    vuint64m8_t data2_v = __riscv_vle64_v_u64m8 (in2, vl);
    vuint64m8_t out_v = __riscv_vle64_v_u64m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vor_vv_u64m8 (data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m8 (uint64_t *out, vuint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    219, 111, 223, 250, 159, 255, 214, 123, 253, 19, 126, 219, 177, 255, 255, 253
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
