/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1212438426, 2848746938, 4266835687, 2678325946, 2851149080, 370416093, 977027059, 2805100712, 4006088096, 4010204946, 1362187212, 1085127525, 3946282153, 3184896465, 2643501206, 3532945589
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    4025659436, 2256852485, 2174561207, 3109422060, 3270020717, 995819983, 1672896782, 877379054, 2153733102, 31832132, 2864038785, 929692075, 2876204248, 745847615, 1345904575, 3279870380
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    3517537528, 374552510, 3222555725, 80389637, 2131916015, 3239797580, 3953981358, 3247369701, 4261697200, 3642508323, 3880502909, 2028736170, 716956161, 3710429411, 3807537574, 238415344
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3517537528, 374552510, 3222555725, 431096114, 418871637, 3239797580, 3953981358, 877379054, 2153733102, 3642508323, 3880502909, 929692075, 716956161, 3710429411, 3807537574, 3279870380
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
