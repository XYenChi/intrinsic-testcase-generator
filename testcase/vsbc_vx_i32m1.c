/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    446744864, 2413669599, 1021351366, 3379187063, 1816938842, 274749931, 1541914293, 1209245365, 969502270, 2862513151, 2675219707, 2412103907, 362974363, 661194075, 1122160696, 1588905468
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    539782216, 819886597, 2876499703, 1202637531, 1576362741, 189994281, 3462112213, 3344700824, 1509916957, 3722621343, 3549399521, 1829255420, 1677799742, 3577817684, 1415606116, 779834040
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vx_i32m1 (data1_v, data2_v, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    -93037352, 1593783002, -1855148337, 2176549532, 240576101, 84755650, -1920197920, -2135455459, -540414687, -860108192, -874179814, 582848487, -1314825379, -2916623609, -293445420, 809071428
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
