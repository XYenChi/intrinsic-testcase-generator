/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2662902171, 1445830565, 1354348891, 1314871616, 576563342, 2625723963, 3618722380, 2767023075, 1536818374, 3037181712, 2396307703, 532163970, 3479453675, 950402921, 800317343, 4226230591
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3667899198, 2779649216, 2621199595, 2020986039, 4237165022, 2932286880, 1605773042, 4244730395, 1544967778, 566271185, 2962757751, 755008692, 963731811, 785344165, 3694274297, 3802237212
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    554389789, 240654832, 1698111998, 163664397, 3088486911, 2515502795, 346700194, 3396565300, 411060671, 1978205899, 1900692611, 1092631673, 939339381, 2865750181, 2067730141, 993195551
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    6330801369, 4225479781, 3975548487, 3335857655, 4813728365, 5558010844, 5224495423, 7011753470, 3081786152, 3603452897, 5359065454, 1287172663, 4443185487, 1735747086, 4494591640, 8028467804
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
