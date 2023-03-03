/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    615599593, 876280321, 3930846112, 3961897294, 422387835, 2526129413, 1072167133, 665312318, 3697887036, 4219802171, 2834707854, 138072035, 1388874943, 3797870927, 880405051, 3550563101
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2153185819, 1041900943, 932596567, 2108569617, 1894507422, 2992194885, 935246612, 3310270678, 3122358460, 355345212, 1630181539, 220419834, 3758679254, 4140291760, 884377118, 3250282192
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    434023483, 2813365930, 4251405842, 3899835697, 516799624, 1859074044, 3131368304, 3255110189, 3515337657, 23106793, 819453595, 57839722, 2842986644, 597727102, 1455936121, 3944894718
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    434023483, 165620622, 932596567, 3899835697, 516799624, 466065472, 3131368304, 3255110189, 3515337657, 23106793, 1630181539, 82347799, 980929368, 597727102, 1455936121, 3250282192
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
