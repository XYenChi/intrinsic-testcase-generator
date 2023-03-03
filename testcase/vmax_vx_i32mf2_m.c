/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3847631264, 1451996157, 188585416, 1424748660, 2111101888, 3945005002, 2449787823, 2889260971, 2639543939, 497211059, 1797354518, 3448933399, 385746629, 3618684975, 2793764798, 1517251413
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    4015481251, 4294099327, 3828023603, 1770549965, 1635884196, 1430277987, 3595460247, 177514838, 2287329743, 3903753596, 1690166808, 1028974382, 349438125, 3197119782, 1759830807, 2541929064
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    1171378330, 2469142938, 2099759573, 404691104, 2627040744, 4206437714, 2062199841, 663886595, 921302846, 511148464, 2843448554, 222697119, 3925034320, 2345682129, 99753090, 634391313
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vx_i32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1171378330, 4294099327, 3828023603, 1770549965, 2627040744, 3945005002, 2062199841, 2889260971, 2639543939, 511148464, 1797354518, 3448933399, 385746629, 2345682129, 2793764798, 2541929064
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
