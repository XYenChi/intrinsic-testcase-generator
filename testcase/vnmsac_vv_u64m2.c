/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    174, 144, 131, 87, 194, 255, 24, 246, 22, 225, 15, 54, 150, 54, 202, 141
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    10, 145, 143, 9, 89, 105, 156, 40, 138, 205, 140, 151, 97, 24, 22, 89
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
        out_v = __riscv_vnmsac_vv_u64m2 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m2 (uint64_t *out, vuint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    18446744073709549877, 18446744073709530736, 18446744073709532883, 18446744073709550833, 18446744073709534350, 18446744073709524842, 18446744073709547872, 18446744073709541776, 18446744073709548580, 18446744073709505491, 18446744073709549517, 18446744073709543463, 18446744073709537066, 18446744073709550321, 18446744073709547172, 18446744073709539067
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
