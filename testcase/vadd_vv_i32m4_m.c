/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1383860963, -1006140159, 860268159, -345151615, 1626736910, -1239344442, 266776683, 343838040, 1871821327, 1767248468, -1765645453, 1938960888, -141931263, -1616544413, 954716016, -1939320999
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    414875137, 2004476122, -1735290865, -1977053203, 754922751, 312535059, 743790443, -575388375, 815258031, 1093176107, 88077624, 54585961, -518802257, 1409770563, -2103872801, 797895520
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int out_data[] = {
    -614589850, -1250717887, -72689404, -1887391136, -1830957442, 2002757373, 1494924717, -1373992365, -1501283525, 642552866, -1029384541, 1203806673, 277234236, 1595855909, 428245769, -1779193995
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32m4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32m4 (bool32_t mask, int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -614589850, -1250717887, -72689403, -1887391136, -1830957441, 2002757373, 1494924717, -1373992364, -1501283524, 642552867, -1029384540, 1203806673, 277234236, 1595855909, 428245769, -1779193994
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
