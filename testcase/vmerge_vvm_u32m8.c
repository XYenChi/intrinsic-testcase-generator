/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3133287556, 1210339389, 4023470186, 4115740893, 969597911, 3206572965, 3181455639, 2660837005, 2783839160, 2088668345, 4091785984, 1727731157, 2278621391, 3968160392, 2862561279, 1770408396
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1208220420, 328353777, 286245436, 3218033020, 1267088751, 3480579356, 2171718445, 3325471772, 2766366431, 887590133, 3065648984, 232125843, 396683934, 943948714, 3621478024, 1966667026
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m8(avl);
    bool4_t masked[] = {
    1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0
    };
    const bool4_t *mask = &masked[0];
    vuint32m8_t data1_v = __riscv_vle32_v_u32m8 (in1, vl);
    vuint32m8_t data2_v = __riscv_vle32_v_i32m8 (in2, vl);
    vuint32m8_t out_v = __riscv_vle32_v_u32m8 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m8 (uint32_t *out, vuint32m8_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1208220420, 328353777, 4023470186, 4115740893, 1267088751, 3480579356, 2171718445, 2660837005, 2766366431, 887590133, 4091785984, 1727731157, 2278621391, 3968160392, 2862561279, 1770408396
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
