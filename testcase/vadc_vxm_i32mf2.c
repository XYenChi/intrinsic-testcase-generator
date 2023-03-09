/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1270753641, 1609379095, 2008983595, -1810619520, -68925573, -1723092907, 264267229, 1528415781, -588181880, -600714042, -593698260, 1858255842, -773268477, 917548159, -624682725, -2117915761
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1314744321, 1027936178, -271584934, -1822868905, 1568687283, 1713598372, 212392617, -365665707, 978586876, -2045488331, -614609494, 88295643, 1064615282, 2026028941, 1652928928, -877512980
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    bool64_t masked[] = {
    0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32mf2 (int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    43990680, 2637315273, 1737398662, -3633488424, 1499761710, -9494534, 476659846, 1162750074, 390404997, -2646202372, -1208307753, 1946551486, 291346805, 2943577100, 1028246204, -2995428740
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
