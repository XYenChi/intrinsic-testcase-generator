/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const uint16_t data1[] = {
    1361, 27987, 12216, 22662, 25982, 25856, 50368, 23525, 55777, 36507, 57186, 45264, 55076, 40868, 9137, 49572
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    59605, 5539, 1, 18351, 18259, 16571, 41009, 38429, 25668, 20300, 55268, 34488, 29084, 62812, 29208, 35685
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m1(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16m1_t data1_v = __riscv_vle16_v_u16m1 (in1, vl);
    vuint16m1_t data2_v = __riscv_vle16_v_u16m1 (in2, vl);
    vuint16m1_t out_v = __riscv_vle16_v_u16m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
		out = __riscv_vadd_vx_u16m1(op1, op2, vl);
        void __riscv_vse16_v_u16m1 (uint16_t *out, vuint16m1_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    60966, 33526, 12217, 41013, 44241, 42427, 25841, 61954, 15909, 56807, 46918, 14216, 18624, 38144, 38345, 19721
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
    5376, 28049, 48857, 4704, 26145, 62492, 43425, 42795, 22470, 1167, 45088, 54340, 2231, 26681, 54315, 5524
    };
    const uint16_t *in1 = &data1[0];
    const uint16_t data2[] = {
    24627, 52179, 5772, 20383, 24467, 55535, 40939, 51163, 61564, 19748, 60009, 40788, 45836, 22259, 21113, 16056
    };
    const uint16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m1(avl);
    const uint16_t out_data[16];
    const uint16_t *out = &out_data[0];
    vuint16m1_t data1_v = __riscv_vle16_v_u16m1 (in1, vl);
    vuint16m1_t data2_v = __riscv_vle16_v_u16m1 (in2, vl);
    vuint16m1_t out_v = __riscv_vle16_v_u16m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_u16m1 (uint16_t *out, vuint16m1_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    uint16_t golden[] = {
    30003, 14692, 54629, 25087, 50612, 52491, 18828, 28422, 18498, 20915, 39561, 29592, 48067, 48940, 9892, 21580
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
