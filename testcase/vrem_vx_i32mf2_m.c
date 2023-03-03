/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2878558077, 3923992082, 2417401092, 3145590460, 2967419247, 3766147483, 3731182716, 3152740780, 3298651498, 1706989062, 156478517, 4150117004, 2468858979, 804430438, 3815295260, 3651565418
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2305685244, 2080145383, 3500208458, 671126544, 934885405, 1806501097, 2266214106, 2308183831, 1149445336, 2265765857, 1914301094, 327470032, 2541952241, 3943780414, 297762700, 1246611800
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int out_data[] = {
    3133541843, 2719180192, 2485600387, 3733639602, 3799813837, 704815615, 3645221629, 4107110079, 2387410472, 578584170, 3524825838, 2595217676, 1697391894, 2471841823, 611244188, 2144276137
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vx_i32mf2_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse32mf2_v_i32 (vbool32_t mask, int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    2305685244, 2080145383, 1082807366, 3733639602, 934885405, 704815615, 3645221629, 2308183831, 1149445336, 578584170, 3524825838, 327470032, 73093262, 2471841823, 611244188, 2144276137
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
