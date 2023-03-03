/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    85846925, 2852377919, 1500444769, 1247796, 3964130435, 1937097465, 1971155078, 3488548458, 669915106, 4179106446, 4143605197, 4252292416, 3598350657, 2773092450, 1802743072, 2860069357
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3308555602, 1687045495, 984082589, 964378178, 2510063071, 910617602, 4216209216, 246936325, 1991612072, 1230611112, 3108595811, 671788410, 3127138164, 2810250696, 1078445880, 3373648485
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    1067825070, 1332667872, 384302392, 593121180, 1723686232, 3878766753, 3925836305, 1173992923, 1447781012, 3701843723, 2255112598, 3456820696, 2869146823, 2419385634, 1366583115, 2397659740
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vx_i32m2_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -3222708678, 1165332423, 516362179, -963130383, 1454067364, 1026479863, -2245054138, 3241612132, -1321696967, 2948495334, 1035009385, 3580504006, 471212493, -37158246, 724297192, -513579128
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
