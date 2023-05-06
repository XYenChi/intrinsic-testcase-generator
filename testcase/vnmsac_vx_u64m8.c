/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    153, 159, 87, 138, 230, 14, 136, 177, 50, 49, 118, 175, 108, 87, 212, 215
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    141, 77, 3, 66, 107, 201, 168, 65, 5, 48, 47, 153, 59, 164, 63, 95
    };
    const uint64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m8(avl);
    const uint64_t out_data[16];
    const uint64_t *out = &out_data[0];
    vuint64m8_t data1_v = __riscv_vle64_v_u64m8 (in1, vl);
    vuint64m8_t data2_v = __riscv_vle64_v_u64m8 (in2, vl);
    vuint64m8_t out_v = __riscv_vle64_v_u64m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vnmsac_vx_u64m8 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m8 (uint64_t *out, vuint64m8_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    18446744073709530044, 18446744073709539373, 18446744073709551355, 18446744073709542509, 18446744073709527006, 18446744073709548803, 18446744073709528768, 18446744073709540111, 18446744073709551367, 18446744073709549264, 18446744073709546071, 18446744073709524841, 18446744073709545245, 18446744073709537349, 18446744073709538261, 18446744073709531192
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
