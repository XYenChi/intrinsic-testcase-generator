/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1267190263, 1231639816, 1379020021, 617606713, 3592052061, 3512863654, 2979321538, 3795003674, 770837356, 3911903866, 3250449790, 1523325396, 735853128, 510863849, 3350278547, 4195510415
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1430836956, 2719978828, 2118342783, 214834638, 571914948, 2002117373, 2460751050, 651562674, 1472592298, 1026940819, 2866831555, 3106400513, 1090446527, 3625205804, 3096422406, 2483105505
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
        out_v = __riscv_vmax_vv_i32mf2 (data1_v, data2_v, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1430836956, 2719978828, 2118342783, 617606713, 3592052061, 3512863654, 2979321538, 3795003674, 1472592298, 3911903866, 3250449790, 3106400513, 1090446527, 3625205804, 3350278547, 4195510415
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
