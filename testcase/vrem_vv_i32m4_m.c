/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1439932363, 717864803, 245366712, 1622289821, 3421155835, 453271467, 62805124, 733779495, 184474784, 1710520506, 4045302934, 1197516100, 224342797, 171433651, 1127362910, 1068298287
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1531216265, 2820748634, 611951867, 3881638113, 2249383800, 4065786912, 954875495, 1243760196, 1521642421, 4276620696, 2785743359, 3810604286, 4255660683, 1663399536, 2399281306, 2086756054
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int out_data[] = {
    2458154710, 2981945621, 2429493755, 3137960216, 1387166340, 3174981905, 3345129474, 3935470541, 1982909319, 3183950607, 1884912440, 2855088978, 1891570458, 3238026839, 419452543, 3968915874
    };
    const int32_t *out = &out_data[0];
    bool8_t masked[] = {
    1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1
    };
    const bool8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4_m (mask, *in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i32m4_m (mask, data1_v, data2_v, vl);
        void vint8_t __riscv_vse32m4_v_i32 (vbool32_t mask, int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    91283902, 667154225, 2429493755, 3137960216, 2249383800, 3174981905, 3345129474, 509980701, 1982909319, 3183950607, 1884912440, 218055986, 217490337, 120496677, 419452543, 1018457767
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
