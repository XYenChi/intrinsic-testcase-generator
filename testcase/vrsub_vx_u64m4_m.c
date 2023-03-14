/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    151, 138, 23, 131, 255, 244, 158, 71, 33, 119, 194, 183, 238, 203, 87, 36
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    219, 23, 209, 49, 129, 153, 215, 136, 233, 251, 125, 178, 149, 144, 67, 163
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m4(avl);
    const uint out_data[] = {
    0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0
    };
    const uint64_t *out = &out_data[0];
    uint16_t masked[] = {
    0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1
    };
    const uint16_t *mask = &masked[0];
    vuint64m4_t data1_v = __riscv_vle64_v_u64m4_m (mask, in1, vl);
    vuint64m4_t data2_v = __riscv_vle64_v_u64m4_m (mask, in2, vl);
    vuint64m4_t out_v = __riscv_vle64_v_u64m4_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrsub_vx_u64m4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m4 (bool64_t mask, uint64_t *out, vuint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    uint64_t golden[] = {
    0, 0, 1, 18446744073709551534, 0, 18446744073709551525, 57, 65, 200, 0, 18446744073709551547, 1, 18446744073709551527, 18446744073709551557, 0, 127
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
