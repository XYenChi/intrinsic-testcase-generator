/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2063153290, 1212119357, 273236611, 165160386, 669860039, -1264871105, -1505285604, -360064508, -225714059, -1256127316, -182736045, 777637788, 823874847, 1695341663, -1336782032, 531819524
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -124331189, -2098588427, -1801925607, 349952366, 1630463906, -880918639, 454510579, -699444069, -1929769771, -948198768, -859210376, -451626339, -402574187, -354669709, -1533489298, -847478678
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    bool16_t masked[] = {
    1, 0, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m2 (int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1938822102, -886469070, -1528688995, 515112753, 2300323946, -2145789744, -1050775024, -1059508576, -2155483830, -2204326083, -1041946420, 326011449, 421300661, 1340671954, -2870271329, -315659154
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
