/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    137, 91, 51, 129, 100, 83, 243, 101, 160, 1, 188, 148, 232, 186, 143, 75
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    44, 118, 200, 81, 50, 136, 91, 89, 8, 79, 97, 248, 73, 198, 200, 234
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    uint32_t masked[] = {
    1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1
    };
    const uint32_t *mask = &masked[0];
    vuint64m2_t data1_v = __riscv_vle64_v_u64m2 (in1, vl);
    vuint64m2_t data2_v = __riscv_vle64_v_u64m2 (in2, vl);
    vuint64m2_t out_v = __riscv_vle64_v_u64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_u64m2 (uint64_t *out, vuint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    44, 118, 200, 129, 100, 136, 91, 89, 8, 79, 97, 248, 73, 198, 143, 234
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
