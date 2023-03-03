/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1253361338, 1018230612, 3691489302, 1327542824, 3722323093, 2036850393, 1540620816, 1637094882, 795378202, 3856965478, 3445509733, 2323720321, 1904047616, 820753108, 1934715030, 2097592388
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1785614027, 354491888, 4046898954, 3445666383, 3270830224, 2907441205, 2662442129, 3787682181, 3975134613, 4163474832, 2997669394, 2455107696, 1004771077, 3323348765, 634291905, 4284093271
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (*in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (*in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vx_i32m2 (data1_v, data2_v, vl);
        void vint32m2_t __riscv_vse32_v_i32 (int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1785614027, 1018230612, 4046898954, 3445666383, 3722323093, 2907441205, 2662442129, 3787682181, 3975134613, 4163474832, 3445509733, 2455107696, 1904047616, 3323348765, 1934715030, 4284093271
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
