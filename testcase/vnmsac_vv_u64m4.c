/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint64_t data1[] = {
    99, 194, 45, 53, 247, 146, 176, 32, 63, 194, 139, 23, 142, 57, 193, 19
    };
    const uint64_t *in1 = &data1[0];
    const uint64_t data2[] = {
    172, 144, 87, 166, 27, 231, 161, 239, 174, 92, 229, 24, 178, 139, 67, 137
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
        out_v = __riscv_vnmsac_vv_u64m4 (out_data, data1_v, data2_v, vl);
        void __riscv_vse64_v_u64m4 (uint64_t *out, vuint64m4_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    uint64_t golden[] = {
    18446744073709534589, 18446744073709523681, 18446744073709547702, 18446744073709542819, 18446744073709544948, 18446744073709517890, 18446744073709523281, 18446744073709543969, 18446744073709540654, 18446744073709533769, 18446744073709519785, 18446744073709551065, 18446744073709526341, 18446744073709543693, 18446744073709538685, 18446744073709549014
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
