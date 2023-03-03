/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3506818757, 3063414123, 528044208, 596149430, 2480701942, 1922476443, 2804889256, 2396863330, 643329812, 3686024954, 697429505, 785640401, 3114722148, 3694248408, 148255785, 148364903
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3516251559, 4238994029, 4248818336, 4290764507, 885077187, 549225886, 1182460053, 3241809201, 95669011, 4010057464, 3678517107, 3712614937, 1268265250, 748044846, 2675168671, 3526136446
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmax_vv_i32m4 (data1_v, data2_v, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    3516251559, 4238994029, 4248818336, 4290764507, 2480701942, 1922476443, 2804889256, 3241809201, 643329812, 4010057464, 3678517107, 3712614937, 3114722148, 3694248408, 2675168671, 3526136446
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
