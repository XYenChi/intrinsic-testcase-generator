/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3650930682, 2312724900, 2158042016, 1042464095, 2940209071, 2318079480, 154550176, 4165436999, 1455536956, 1354948613, 3401457505, 805923398, 2094998260, 3503600582, 3099895841, 2134021863
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1271849144, 3842053764, 3405232559, 1030262439, 1143869798, 1172044400, 10685405, 1405279788, 136765465, 3603203395, 194930417, 2359725026, 3690711191, 4012944220, 617266371, 3235313846
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int out_data[] = {
    1929638930, 1982904403, 1960090546, 627548736, 4250964057, 3748935689, 170743615, 3151318160, 3998156242, 4280277018, 3605216009, 2465034603, 3500291514, 1691898992, 1947941542, 115660140
    };
    const int32_t *out = &out_data[0];
    bool4_t masked[] = {
    0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8_m (mask, *in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i32m8_m (mask, data1_v, data2_v, vl);
        void vint4_t __riscv_vse32m8_v_i32 (vbool32_t mask, int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1929638930, 1, 1, 627548736, 0, 0, 170743615, 0, 0, 2, 0, 2, 1, 1, 1947941542, 1
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
