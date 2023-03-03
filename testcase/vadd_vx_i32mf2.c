/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1570344186, 2910976663, 1691834555, 1058783424, 2974307976, 813329340, 550499771, 1868990430, 3806429564, 2708244794, 4286126513, 2369417823, 3002652735, 2306902296, 4221088923, 2514762210
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3775384739, 2772978279, 2383064555, 297788223, 2672200542, 110432661, 2747947945, 3345948360, 1589039151, 666248685, 2550691558, 810144136, 2642142925, 4291826245, 2664367323, 1593016878
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
        out_v = __riscv_vadd_vx_i32mf2 (data1_v, data2_v, vl);
        void vint32mf2_t __riscv_vse32_v_i32 (int32mf2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    5345728925, 5683954942, 4074899110, 1356571647, 5646508518, 923762001, 3298447716, 5214938790, 5395468715, 3374493479, 6836818071, 3179561959, 5644795660, 6598728541, 6885456246, 4107779088
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
