/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1116794183, 1220662072, 798391049, 1831420161, 1353399830, -1421753695, 1079471431, -1058732009, -670166154, -855256847, 1867455863, -1751881966, -151693887, -738026222, -798673117, -1378557830
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -493555806, 1990184716, 1998902920, 1568639307, -755231287, -792853590, -1275979087, 806185335, -1626241513, -445004266, 1833897852, 1286717691, -734244909, 782751538, -1132399655, 2076137951
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int out_data[] = {
    1995419076, -5815053, -472986757, 585414457, 665570520, -1601114080, 1975491283, 2093827758, -1328320288, -380574115, -2115548672, 1751049926, -56562233, -817376851, -1948737880, 1642614557
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u32mf2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32mf2 (bool32_t mask, int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1995419076, -5815052, -472986756, 585414458, 665570521, -1601114079, 1975491284, 2093827759, -1328320287, -380574115, -2115548671, 1751049927, -56562233, -817376850, -1948737879, 1642614557
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
