/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -949899101, -1272394055, -1532073836, 474251318, -1648392923, -1193521541, -1656100662, 42568094, 223604157, -1014112553, 746622006, -354372632, 405590561, 996576900, -1312774851, 1808572049
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    798314373, -1471189131, 742857155, 991131014, 617520376, 1677751527, 1805273789, -1996201781, 1672491961, 1435266546, -788886136, 274171978, 198785919, -1540646827, -1462576612, 888475106
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int out_data[] = {
    1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 0
    };
    const int32_t *out = &out_data[0];
    uint16_t masked[] = {
    0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1
    };
    const uint16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m2 (int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1, 0, 3505750615, 1465382332, 1, 0, 0, 2341333609, 1896096118, 421153993, 1, 4214766642, 1, 3750897369, 1, 2697047155
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
