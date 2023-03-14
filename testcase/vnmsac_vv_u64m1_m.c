/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    129, 53, 86, 44, 181, 16, 66, 169, 137, 75, 232, 38, 204, 42, 197, 211
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    2, 78, 231, 210, 168, 191, 42, 122, 216, 181, 92, 55, 16, 117, 106, 28
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m1(avl);
    const uint out_data[] = {
    1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1
    };
    const uint64_t *out = &out_data[0];
    uint64_t masked[] = {
    1, 0, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0
    };
    const uint64_t *mask = &masked[0];
    vuint64m1_t data1_v = __riscv_vle64_v_u64m1_m (mask, in1, vl);
    vuint64m1_t data2_v = __riscv_vle64_v_u64m1_m (mask, in2, vl);
    vuint64m1_t out_v = __riscv_vle64_v_u64m1_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vv_u64m1_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m1 (bool64_t mask, uint64_t *out, vuint64m1_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    18446744073709551359, 1, 18446744073709531750, 18446744073709542376, 18446744073709521208, 0, 0, 18446744073709530999, 18446744073709522025, 1, 18446744073709530273, 18446744073709549526, 0, 18446744073709546702, 1, 1
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
