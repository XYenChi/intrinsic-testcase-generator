/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2005707869, 3202422657, 1645322331, 986022082, 2295638792, 1542480504, 674997494, 3540499400, 153528871, 2299878501, 3553782780, 4003816844, 3714334229, 688000061, 2872476400, 3584111027
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3225008219, 572179697, 2763274210, 761346469, 3913792518, 793926317, 3563039533, 3254124023, 2885925443, 91702632, 1135451229, 1119656209, 1075700353, 1734144330, 256059615, 2098104546
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i32mf2 (data1_v, data2_v, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1219300350, 572179697, 1117951879, 761346469, 1618153726, 793926317, 188052063, 3254124023, 122405765, 91702632, 1135451229, 1119656209, 1075700353, 358144208, 256059615, 2098104546
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
