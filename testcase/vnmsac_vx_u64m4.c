/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    222, 77, 227, 198, 177, 0, 126, 2, 32, 64, 28, 76, 205, 103, 254, 211
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    96, 102, 244, 108, 175, 178, 95, 142, 171, 6, 10, 234, 70, 52, 28, 91
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
        out_v = __riscv_vnmsac_vx_u64m4 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m4 (uint64_t *out, vuint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    18446744073709530304, 18446744073709543762, 18446744073709496228, 18446744073709530232, 18446744073709520642, 0, 18446744073709539646, 18446744073709551333, 18446744073709546145, 18446744073709551232, 18446744073709551336, 18446744073709533833, 18446744073709537266, 18446744073709546260, 18446744073709544504, 18446744073709532416
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
