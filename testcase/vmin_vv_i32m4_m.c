/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2801678565, 2381287432, 3857359973, 1665520688, 21152006, 3344054121, 3758837002, 637014819, 2264418678, 2833831004, 1058839281, 2051675946, 3217831616, 1350749069, 3239039317, 2627444633
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    654577575, 3894213653, 1324642323, 4142492021, 2442635786, 4061396050, 3156713405, 2967640327, 1108736038, 486162255, 213113015, 3252607927, 4247431663, 2227342524, 1017447500, 800627706
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    1998690893, 148217203, 2750529384, 956098008, 2576432232, 3675597728, 769089109, 373200454, 2726899574, 3761361072, 72483755, 3391425421, 4276392132, 3338024021, 4132851656, 223445149
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    2801678565, 148217203, 3857359973, 956098008, 2442635786, 3675597728, 769089109, 373200454, 2726899574, 2833831004, 1058839281, 3252607927, 4276392132, 2227342524, 3239039317, 223445149
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
