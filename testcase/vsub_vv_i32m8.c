/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2075975345, 3367856220, 43463225, 504193640, 1127096346, 471276042, 2206103110, 838832640, 1308038499, 2004473896, 3329253463, 163034180, 907417572, 2594305207, 3841707414, 2027299055
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    998556701, 589537403, 3103885349, 99123809, 3885205621, 594965264, 955536395, 1212454293, 259935746, 892848828, 2637141241, 285615492, 2656916039, 3625127473, 1647487023, 2232883229
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsub_vv_u32m8 (data1_v, data2_v, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1077418644, 2778318817, -3060422124, 405069831, -2758109275, -123689222, 1250566715, -373621653, 1048102753, 1111625068, 692112222, -122581312, -1749498467, -1030822266, 2194220391, -205584174
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
