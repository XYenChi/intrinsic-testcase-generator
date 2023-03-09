/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2084272237, -137505237, -106814814, -1390327868, 603994467, -928301435, 1760635806, -1496453539, -750886708, -1033934977, 1051791695, 1093286839, 145340207, 900446080, -664381649, -1070257296
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1405249777, 894026896, 953516651, 1382358593, -1675737678, 1787939966, -1629782489, -297910770, 1103490774, 520766053, 77569981, -741525095, -1741305663, 642679632, 84732248, -1755477936
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    bool16_t masked[] = {
    0, 1, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 0
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
    2084272237, 894026896, -106814814, 1382358593, -1675737678, -928301435, 1760635806, -297910770, -750886708, 520766053, 77569981, -741525095, 145340207, 642679632, 84732248, -1070257296
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
