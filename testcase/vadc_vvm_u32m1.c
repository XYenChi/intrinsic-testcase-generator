/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3722096036, 3998239108, 1710788377, 2297644052, 489345186, 632163113, 3574224715, 4025414444, 233961244, 1141507499, 2071152543, 4236426653, 3952666364, 1496199691, 1945417965, 2774359344
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    100988315, 2093134736, 4115975696, 3199769147, 2362995001, 3805740602, 2486568899, 1335920928, 462319775, 3760276606, 1449137926, 1598697105, 503239479, 1018657787, 1056301685, 1621622042
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m1(avl);
    bool32_t masked[] = {
    1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0
    };
    const bool32_t *mask = &masked[0];
    vuint32m1_t data1_v = __riscv_vle32_v_u32m1 (in1, vl);
    vuint32m1_t data2_v = __riscv_vle32_v_i32m1 (in2, vl);
    vuint32m1_t out_v = __riscv_vle32_v_u32m1 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m1 (uint32_t *out, vuint32m1_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3823084352, 6091373844, 5826764073, 5497413199, 2852340187, 4437903716, 6060793614, 5361335373, 696281019, 4901784105, 3520290469, 5835123759, 4455905844, 2514857478, 3001719651, 4395981386
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
