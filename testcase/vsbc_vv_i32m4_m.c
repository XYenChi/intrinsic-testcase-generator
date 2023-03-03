/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4288873348, 1954836384, 2858666310, 447343074, 4153444811, 1484488414, 798794632, 2629877194, 1171554793, 3681552319, 989631179, 799059703, 1694649634, 1452383486, 860779287, 4272876870
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1917277758, 3000534496, 924679584, 2284376040, 2084293418, 239027738, 380151464, 1678436172, 886851582, 1516957656, 1573761940, 1777992425, 648311681, 1832846153, 1202522836, 2862441969
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    4185183586, 2018921947, 2833884655, 2059529410, 4225705530, 3018815272, 986043727, 2003139628, 1270609693, 730766483, 1356946052, 4165307403, 3468433889, 1433513593, 2693950468, 880182400
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    2371595590, -1045698112, 1933986726, -1837032967, 2069151392, 1245460675, 418643168, 951441021, 284703211, 2164594662, -584130761, -978932723, 1046337953, -380462667, -341743549, 1410434901
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
