/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    3225785365290961313, 855853058062554627, -6772880831685963573, 498189874821136815, 9223255491697928867, 5518279668695348816, -2995045759136878421, -7169448786009070127, -3792051505921698676, 6462780310620522442, -1428848134256742985, 8669490084740866163, -6097790421965444765, 3786542154406504451, 3815658935870659406, -4095248070557583436
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    -2499973757753668063, 3426716163742541745, -1263282977945540663, 2838604482761662163, -8530080191552590668, 4152741079778362576, 4324325489988792218, 990930353472292043, -4821162232431282942, 2841928273061315556, 3739279066609015230, -5702767891938436963, -4011009999414193862, -7724068448495464264, 4957701847635458507, 6286454555561512234
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e64m2(avl);
    bool32_t masked[] = {
    0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint64m2_t data1_v = __riscv_vle64_v_i64m2 (in1, vl);
    vint64m2_t data2_v = __riscv_vle64_v_i64m2 (in2, vl);
    vint64m2_t out_v = __riscv_vle64_v_i64m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse64_v_i64m2 (int64_t *out, vint64m2_t out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
        mask += 8;
      }
    int64_t golden[] = {
    3225785365290961313, 3426716163742541745, -1263282977945540663, 2838604482761662163, -8530080191552590668, 5518279668695348816, -2995045759136878421, 990930353472292043, -4821162232431282942, 2841928273061315556, 3739279066609015230, 8669490084740866163, -4011009999414193862, 3786542154406504451, 4957701847635458507, -4095248070557583436
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
