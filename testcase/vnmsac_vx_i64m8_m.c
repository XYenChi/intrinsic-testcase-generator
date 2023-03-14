/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    40, -10, 123, -112, -126, -106, -39, 57, 0, -92, -72, 101, 75, 114, -88, -100
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    70, 10, -55, -84, 78, -84, 109, -120, -84, -37, 74, -87, 122, -24, 114, 109
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const int out_data[] = {
    1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1
    };
    const int64_t *out = &out_data[0];
    uint8_t masked[] = {
    1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1
    };
    const uint8_t *mask = &masked[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8_m (mask, in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8_m (mask, in2, vl);
    vint64m8_t out_v = __riscv_vle64_v_i64m8_m (mask, out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vx_i64m8_m (mask, out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_i64m8 (bool64_t mask, int64_t *out, vint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    18446744073709548817, 1, 6765, 0, 0, 1, 4251, 1, 1, 0, 0, 0, 1, 2737, 1, 10901
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
