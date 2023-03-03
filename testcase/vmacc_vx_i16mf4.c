/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    52243, 34655, 59939, 4681, 4260, 39641, 22372, 61563, 50866, 31370, 41165, 46203, 44977, 42290, 13997, 61349
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    22869, 38101, 32045, 50192, 44859, 59681, 37251, 24356, 22465, 5596, 61893, 11634, 6631, 19363, 16251, 24395
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4 (*in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4 (*in2, vl);
    vint16mf4_t out_v = __riscv_vle16_v_i16mf4 (*out, vl);
    const int out_data[] = {
    60518, 13425, 24729, 37255, 52081, 53594, 10907, 56493, 26545, 45327, 61918, 25560, 29031, 40325, 29650, 16134
    };
    const int16_t *out = &out_data[0];
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i16mf4 (data1_v, data2_v, vl);
        void vint16mf4_t __riscv_vse16_v_i16 (int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    1194805685, 1320403580, 1920769984, 234986007, 191151421, 2365868115, 833390279, 1499484921, 1142731235, 175591847, 2547887263, 537551262, 298271518, 818901595, 227494897, 1496624989
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
