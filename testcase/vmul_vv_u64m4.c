/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    74, 38, 227, 95, 139, 84, 199, 86, 100, 164, 230, 240, 242, 250, 141, 153
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    101, 103, 12, 36, 220, 95, 49, 85, 100, 36, 20, 166, 105, 1, 204, 103
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const uint64_t out_data[16];
    const uint64_t *out = &out_data[0];
    vuint64m4_t data1_v = __riscv_vle64_v_u64m4 (in1, vl);
    vuint64m4_t data2_v = __riscv_vle64_v_u64m4 (in2, vl);
    vuint64m4_t out_v = __riscv_vle64_v_u64m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i64m4 (data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m4 (uint64_t *out, vuint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    7474, 3914, 2724, 3420, 30580, 7980, 9751, 7310, 10000, 5904, 4600, 39840, 25410, 250, 28764, 15759
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
