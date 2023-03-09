/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1002932923, 1456958806, -1321879227, -949515694, -683245952, 1614272187, 335090692, 1936352703, 1688001643, 558348184, 1991923931, -811168641, 1748306475, -873527667, -947264958, 1094570772
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1031201071, 1184349982, -468702533, 2021283890, -37903894, -1605473362, 1588966721, 1278819436, 88940501, 1206155365, 1421329882, -1495166001, 2058479554, -1692657508, -602092266, 1787902758
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    bool4_t masked[] = {
    0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1
    };
    const bool4_t *mask = &masked[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m8 (int32_t *out, vint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    28268148, 2641308788, -1790581760, 1071768197, -721149845, 8798825, 1924057414, 3215172140, 1776942144, 1764503549, 3413253814, -2306334641, 3806786029, -2566185174, -1549357224, 2882473531
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
