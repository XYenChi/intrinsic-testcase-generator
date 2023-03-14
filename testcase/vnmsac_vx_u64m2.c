/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    15, 89, 203, 120, 68, 109, 129, 190, 133, 45, 161, 76, 72, 122, 98, 156
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    227, 142, 54, 66, 13, 9, 235, 156, 211, 202, 36, 12, 131, 113, 186, 220
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    const uint64_t out_data[16];
    const uint64_t *out = &out_data[0];
    vuint64m2_t data1_v = __riscv_vle64_v_u64m2 (in1, vl);
    vuint64m2_t data2_v = __riscv_vle64_v_u64m2 (in2, vl);
    vuint64m2_t out_v = __riscv_vle64_v_u64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vx_u64m2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m2 (uint64_t *out, vuint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    18446744073709548212, 18446744073709538978, 18446744073709540655, 18446744073709543696, 18446744073709550732, 18446744073709550636, 18446744073709521302, 18446744073709521977, 18446744073709523554, 18446744073709542527, 18446744073709545820, 18446744073709550704, 18446744073709542184, 18446744073709537830, 18446744073709533388, 18446744073709517297
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
