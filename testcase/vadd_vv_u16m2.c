/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    1209, 36258, 37905, 21789, 52193, 52825, 54553, 37735, 5200, 54575, 25707, 53720, 6239, 40769, 3958, 36413
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    58977, 48224, 44244, 3461, 22251, 3277, 40056, 60555, 63138, 43221, 64926, 63011, 57110, 62702, 37117, 57043
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16m2_t data1_v = __riscv_vle16_v_u16m2 (in1, vl);
    vuint16m2_t data2_v = __riscv_vle16_v_u16m2 (in2, vl);
    vuint16m2_t out_v = __riscv_vle16_v_u16m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vv_u16m2(op1, op2, vl);
        void __riscv_vse16_v_u16m2 (uint16_t *out, vuint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    60186, 18946, 16613, 25250, 8908, 56102, 29073, 32754, 2802, 32260, 25097, 51195, 63349, 37935, 41075, 27920
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
/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    7937, 39933, 3456, 44626, 42655, 21980, 14435, 23271, 25636, 51904, 58589, 6885, 31750, 40872, 45155, 32049
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    3500, 25031, 10224, 55430, 59928, 29706, 40977, 52915, 40193, 36594, 5087, 63904, 8822, 7025, 42876, 38609
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m2(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16m2_t data1_v = __riscv_vle16_v_u16m2 (in1, vl);
    vuint16m2_t data2_v = __riscv_vle16_v_u16m2 (in2, vl);
    vuint16m2_t out_v = __riscv_vle16_v_u16m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16m2 (uint16_t *out, vuint16m2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    11437, 64964, 13680, 34520, 37047, 51686, 55412, 10650, 293, 22962, 63676, 5253, 40572, 47897, 22495, 5122
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
