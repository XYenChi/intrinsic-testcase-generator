/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    37, 53, 252, 204, 253, 206, 136, 175, 79, 74, 242, 52, 181, 84, 21, 42
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    62, 237, 199, 51, 251, 45, 111, 224, 24, 209, 190, 109, 152, 200, 53, 254
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const uint out_data[] = {
    0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0
    };
    const uint64_t *out = &out_data[0];
    uint16_t masked[] = {
    0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0
    };
    const uint16_t *mask = &masked[0];
    vuint64m4_t data1_v = __riscv_vle64_v_u64m4_m (mask, in1, vl);
    vuint64m4_t data2_v = __riscv_vle64_v_u64m4_m (mask, in2, vl);
    vuint64m4_t out_v = __riscv_vle64_v_u64m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsub_vv_u64m4_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m4 (bool64_t mask, uint64_t *out, vuint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    0, 18446744073709551432, 53, 153, 2, 0, 136, 18446744073709551567, 79, 0, 0, 52, 1, 18446744073709551500, 18446744073709551584, 0
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
