/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    62, 14, 74, 151, 210, 163, 224, 204, 237, 51, 153, 65, 55, 28, 23, 6
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    76, 148, 204, 161, 99, 4, 199, 59, 199, 97, 9, 36, 2, 73, 26, 241
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const uint out_data[] = {
    0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1
    };
    const uint64_t *out = &out_data[0];
    uint32_t masked[] = {
    0, 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1
    };
    const uint32_t *mask = &masked[0];
    vuint64m2_t data1_v = __riscv_vle64_v_u64m2_m (mask, in1, vl);
    vuint64m2_t data2_v = __riscv_vle64_v_u64m2_m (mask, in2, vl);
    vuint64m2_t out_v = __riscv_vle64_v_u64m2_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_u64m2 (bool64_t mask, uint64_t *out, vuint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    62, 14, 74, 302, 420, 163, 448, 408, 474, 102, 306, 65, 55, 56, 23, 12
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
