/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1547563879, 705091285, 3726605916, 4294590563, 851456866, 874756496, 3624302674, 3534907739, 617645621, 372735584, 81922341, 291928364, 4162759132, 786709056, 3767277212, 3784487555
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1853649638, 964428699, 1528789609, 4210498231, 277224499, 4234576892, 578622018, 4257051512, 2010432760, 4226103788, 782533778, 4019381726, 4209890912, 875643895, 1856327841, 3658891413
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1 (*in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1 (*in2, vl);
    vint32m1_t out_v = __riscv_vle32_v_i32m1 (*out, vl);
    const int out_data[] = {
    348224685, 1319365110, 603301401, 1634750264, 801340526, 1953553501, 1296629164, 1936931417, 3729392941, 528495133, 3635541018, 814106629, 2345215520, 615028666, 4283953173, 3929807082
    };
    const int32_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i32m1 (data1_v, data2_v, vl);
        void vint32m1_t __riscv_vse32_v_i32 (int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    2868641224438450487, 680010271988153325, 5697196401822028245, 18082365970015544317, 236044703898300660, 3704223646042043933, 2097101328369305296, 15048284337027382785, 1241734994258336901, 1575219263993287325, 64107002640875316, 1173371532376782893, 17524761840997023904, 688876982642641786, 6993301577684412465, 13847029021524672297
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
