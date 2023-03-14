/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    95, 11, 129, 145, 152, 191, 28, 24, 32, 52, 156, 75, 57, 88, 112, 99
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    76, 168, 127, 183, 212, 215, 76, 40, 140, 163, 183, 54, 40, 247, 4, 154
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    uint8_t masked[] = {
    1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1
    };
    const uint8_t *mask = &masked[0];
    vuint64m8_t data1_v = __riscv_vle64_v_u64m8 (in1, vl);
    vuint64m8_t data2_v = __riscv_vle64_v_u64m8 (in2, vl);
    vuint64m8_t out_v = __riscv_vle64_v_u64m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_u64m8 (uint64_t *out, vuint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    172, 180, 256, 329, 364, 407, 104, 64, 173, 215, 339, 130, 98, 336, 117, 254
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
