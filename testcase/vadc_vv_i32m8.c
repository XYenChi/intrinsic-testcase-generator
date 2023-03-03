/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2972554251, 1114988515, 599758064, 113124769, 3870851973, 3585230722, 3685641743, 336712125, 4243682005, 4225335631, 202731894, 1815425696, 652571212, 3717501415, 3562308019, 2440030747
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    454871248, 3397020899, 2276797671, 3661150182, 523671500, 812151400, 1145942196, 2171843732, 3018797173, 2753651361, 1205583356, 2736991522, 2905868345, 945244349, 1104401947, 3636416394
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vv_i32m8 (data1_v, data2_v, mask, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3427425499, 4512009414, 2876555735, 3774274951, 4394523473, 4397382122, 4831583939, 2508555857, 7262479178, 6978986992, 1408315250, 4552417218, 3558439557, 4662745764, 4666709966, 6076447141
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
