/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    4067525285, 976989717, 665440427, 2958486336, 2539728821, 1930864588, 816542440, 4204256148, 697197344, 2279016939, 1138483877, 915421016, 3417858022, 3466391219, 3091910196, 4241748636
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1914584177, 134961329, 3776527514, 1804813604, 631482160, 960288516, 1435631856, 216457917, 158324674, 2603617219, 1301565406, 3408394315, 3851418430, 2840326748, 3727624987, 2526645028
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32mf2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (*in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (*in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadc_vv_i32mf2 (data1_v, data2_v, mask, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    5982109462, 1111951046, 4441967941, 4763299940, 3171210981, 2891153104, 2252174296, 4420714065, 855522018, 4882634158, 2440049283, 4323815331, 7269276452, 6306717967, 6819535183, 6768393664
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
