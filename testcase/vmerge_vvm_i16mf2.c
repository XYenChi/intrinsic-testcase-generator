/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    29773, -30743, 25217, 24942, -31875, -19252, 31884, -24014, -26200, -19859, 22994, 2835, -2220, 14563, -9114, 24664
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    -17615, 31881, -23033, 31215, 855, 29264, 13386, -29591, -10776, -9110, 10552, -9022, 218, -16653, 28018, -23776
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16mf2(avl);
    bool32_t masked[] = {
    0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vint16mf2_t data1_v = __riscv_vle16_v_i16mf2 (in1, vl);
    vint16mf2_t data2_v = __riscv_vle16_v_i16mf2 (in2, vl);
    vint16mf2_t out_v = __riscv_vle16_v_i16mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse16_v_i16mf2 (int16_t *out, vint16mf2_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    29773, 31881, -23033, 31215, 855, 29264, 31884, -24014, -10776, -9110, 10552, -9022, 218, -16653, 28018, 24664
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
