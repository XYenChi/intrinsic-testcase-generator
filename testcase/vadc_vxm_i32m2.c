/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -2079229826, 1335652975, 615761181, -1510049898, 931180176, 2145609948, -187665816, 1313628698, -1839790935, -188381488, -405479591, -93204433, -248699846, -902906729, 743832346, 1547607141
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -1586540095, -1755120411, 487940625, 1168828599, -1449490300, 1665190169, -518780905, -2145775603, 761891587, 177229916, -306795803, 1510305193, -1977219345, 1623579501, 980279205, 1714620447
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    bool16_t masked[] = {
    1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m2 (int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -3665769920, -419467435, 1103701806, -341221299, -518310123, 3810800117, -706446721, -832146905, -1077899348, -11151571, -712275394, 1417100760, -2225919190, 720672773, 1724111552, 3262227588
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
