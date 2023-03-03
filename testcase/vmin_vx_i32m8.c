/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    749078103, 2070021308, 2438251686, 1783950247, 566060727, 519015435, 542650348, 1732641123, 4239597446, 1166744014, 926500077, 1466857086, 2349114028, 1595287087, 2331622768, 3545316391
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    843038301, 3177659841, 2965724272, 1042231890, 567495741, 337026299, 3259010753, 614336880, 522262563, 3610961648, 3731940121, 965144343, 3072026724, 2243392602, 163272651, 1104497745
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
        out_v = __riscv_vmin_vx_i32m8 (data1_v, data2_v, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    843038301, 3177659841, 2965724272, 1783950247, 567495741, 519015435, 3259010753, 1732641123, 4239597446, 3610961648, 3731940121, 1466857086, 3072026724, 2243392602, 2331622768, 3545316391
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
