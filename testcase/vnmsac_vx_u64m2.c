/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    224, 233, 57, 37, 168, 237, 13, 2, 235, 13, 189, 102, 122, 234, 173, 68
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    157, 27, 61, 122, 182, 221, 109, 197, 250, 172, 59, 172, 142, 187, 184, 249
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
    18446744073709516448, 18446744073709545326, 18446744073709548140, 18446744073709547103, 18446744073709521041, 18446744073709499239, 18446744073709550199, 18446744073709551222, 18446744073709492867, 18446744073709549380, 18446744073709540466, 18446744073709534072, 18446744073709534292, 18446744073709507859, 18446744073709519784, 18446744073709534685
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
