/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3862423392, 593620798, 3308438539, 2503087388, 840751905, 739442011, 693357367, 2440381776, 1648600549, 4149864963, 4294194803, 3357320814, 1789066981, 3935422467, 37307955, 2806233367
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    753033864, 249911023, 56745183, 87180812, 1552027735, 1641290844, 2588531801, 728822697, 1044984992, 1479135265, 1150235967, 1066780911, 144452397, 927083328, 2369540438, 3358860688
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    3758663039, 2517374455, 3691787902, 3852215701, 3633359666, 342751525, 2365068732, 2925357749, 1993305553, 3048414091, 1761705090, 3178085577, 3040037819, 2969545429, 2850298537, 631927429
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vrem_vv_i32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3758663039, 2517374455, 56745183, 87180812, 3633359666, 162406822, 508459700, 728822697, 1993305553, 1479135265, 1150235967, 1066780911, 144452397, 2969545429, 2850298537, 552627321
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
