/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2833678097, 2508234079, 1254482339, 2563468931, 305276163, 3254051261, 2099231534, 1825237984, 1482511784, 1598062041, 3460981572, 2693541260, 1946216790, 4246845734, 1455859904, 735157162
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1936414645, 3395260700, 3819840579, 807852557, 1228365944, 641498730, 3108292484, 847733652, 3990088356, 3951155599, 1751986500, 3244235847, 2426792556, 3431946681, 4136253145, 2268082580
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i32m2 (data1_v, data2_v, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    5487175766246530565, 8516108594829395300, 4791922544151034281, 2070904930698406567, 374990842144192872, 2087469751286398530, 6525025599307990456, 1547315661945437568, 5915353006971187104, 6314191780846517559, 6063592990892778000, 8738483111065547220, 4723064418334215240, 14574948121520308854, 6021805106599398080, 1667397152694437960
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
