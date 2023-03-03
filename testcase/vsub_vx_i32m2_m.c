/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2765841039, 4010789622, 856182344, 2443867956, 888360776, 23013677, 2409507057, 2888723324, 3214105126, 1122067120, 1973916999, 2879184893, 3595206020, 368524734, 1476645646, 1466537978
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1109828912, 2469213554, 2569081604, 1355892772, 584910657, 3784616697, 4279788608, 259737063, 54180723, 1312771919, 3155456219, 736484773, 1953214969, 2838096596, 3644908655, 93364992
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    2116230046, 4175568407, 22805401, 1885920316, 1798512252, 1570168489, 2261562825, 1913688985, 3687934366, 4053256242, 192067322, 171205686, 2524857990, 3116878782, 3088455569, 2629205886
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vx_u32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1656012127, 1541576068, 22805401, 1885920316, 303450119, -3761603020, -1870281551, 1913688985, 3687934366, 4053256242, -1181539220, 2142700120, 2524857990, -2469571862, 3088455569, 2629205886
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
