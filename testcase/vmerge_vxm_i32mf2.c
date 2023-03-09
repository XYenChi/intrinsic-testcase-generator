/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1882567214, -1907257297, -667344562, 1302185485, -1766438392, 1425258879, -1107032572, 275699386, -271652060, 2125262086, 1634305443, -1909432851, -865168577, 1923134037, -552712080, 1750271461
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1196787415, -50528751, 6107419, 1241335905, 330057034, -1578098031, -1028691794, -481089524, 430538619, -2052716545, 1207329720, 1226966763, -1123671788, -416763929, 333825295, -1746025452
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    bool64_t masked[] = {
    1, 0, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0
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
    1196787415, -1907257297, 6107419, 1241335905, -1766438392, 1425258879, -1107032572, -481089524, -271652060, 2125262086, 1207329720, -1909432851, -1123671788, -416763929, 333825295, 1750271461
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
