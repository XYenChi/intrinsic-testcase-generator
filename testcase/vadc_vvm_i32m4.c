/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -333131559, -991553798, 1860981049, -1023274537, -2032633413, 556583171, -2028265691, -719367472, 353853777, 916911970, -1817059314, 576384588, -1593285493, -1699842411, -935877883, -505789395
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -1313163431, 657278463, 1426691153, 1764382759, -1262489617, 2016017197, -338580589, 823094125, -1761670419, -1260784055, 854617158, 600188302, 1267522779, -1116697837, -1463620118, 1759200939
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    bool8_t masked[] = {
    0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m4 (int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -1646294990, -334275334, 3287672202, 741108223, -3295123030, 2572600368, -2366846280, 103726653, -1407816642, -343872085, -962442156, 1176572891, -325762713, -2816540248, -2399498000, 1253411545
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
