/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4236689470, 1902988507, 2389298851, 2157314678, 2194602098, 1082558910, 414230456, 895514771, 688822418, 3763750153, 2076394001, 3988567353, 520310729, 1835198530, 1966965572, 3797326623
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    686129132, 73722060, 3263791090, 1030565223, 3900115527, 2567149541, 905634072, 546236159, 1896129524, 4012024425, 103358089, 59075649, 1396029171, 2011768302, 2288873497, 711667
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
        out_v = __riscv_vadd_vv_i32m2 (data1_v, data2_v, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    4922818602, 1976710567, 5653089941, 3187879901, 6094717625, 3649708451, 1319864528, 1441750930, 2584951942, 7775774578, 2179752090, 4047643002, 1916339900, 3846966832, 4255839069, 3798038290
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
