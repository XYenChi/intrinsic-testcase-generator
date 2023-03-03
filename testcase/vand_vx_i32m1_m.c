/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    148929285, 318167198, 2991844380, 2405595948, 2659753969, 82015450, 1881665954, 1557705759, 4039888575, 3037611365, 3339728841, 3975979627, 3103732349, 3012522471, 1933834226, 284396370
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    4254288449, 2357241608, 3159124783, 1306203236, 2202893300, 3761228060, 1429574949, 1553541474, 3232886764, 486938816, 3354743738, 735007708, 2235714389, 1436630597, 1340258490, 155037099
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    3007227785, 882654865, 2421263357, 2217399049, 3449954603, 4003358941, 715437008, 2010575956, 4214995340, 212710158, 3572089371, 2125512324, 205350671, 341577714, 3911559353, 238912454
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3007227785, 882654865, 3159124783, 1306203236, 3449954603, 4003358941, 1429574949, 2010575956, 3232886764, 212710158, 3572089371, 2125512324, 2235714389, 1436630597, 3911559353, 155037099
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
