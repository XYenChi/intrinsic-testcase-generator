/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -135350200, -1742320045, -1226658525, 1072115835, -1532474264, 1466735198, 96372735, -1171398233, -1778824272, -907353189, -2054441474, 897335979, -744710923, 431287493, 822811593, -1089892360
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    165358587, -195016261, -1012748155, 2023808504, -507706711, 12035538, -992198191, 807187092, 803387284, -673016693, -489135306, -1319836878, -2048314952, 729549372, 669680232, -547227034
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32m2 (data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m2 (int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1332985742, -365453373, -1393717851, 911957869, -876507330, 983243237, -1709448343, -1836198465, -2257872385, -111337869, -472105254, 2852036074, 995319028, 34146541, -906371741, 956738535
    };
    int fail = 0;
    for (int i = 0; i < 16; i++){
        if (golden[i] != out_data[i]) {
            printf ("idx=%d golden=%d out=%d\n", i, golden[i], out_data[i]);
            fail++;
            }
        }
    if (fail) {
        return 1;
    } else {
        return 0;
    }
}
