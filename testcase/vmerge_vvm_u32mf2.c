/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    557461641, 1145951932, 127879953, 1507270211, 2077116967, 3663030929, 2168217887, 2411428961, 2882201724, 3676276935, 4043955814, 2613130448, 3145360875, 771978288, 3542954665, 1689291514
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    3405413005, 199762714, 1492549934, 1349693257, 3050351926, 648139036, 3408827113, 1685957243, 45074849, 2300292735, 3072915404, 1539297202, 2027447957, 3672700471, 1337044258, 1717809472
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    bool64_t masked[] = {
    1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1
    };
    const bool64_t *mask = &masked[0];
    vuint32mf2_t data1_v = __riscv_vle32_v_u32mf2 (in1, vl);
    vuint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (in2, vl);
    vuint32mf2_t out_v = __riscv_vle32_v_u32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32mf2 (uint32_t *out, vuint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    3405413005, 199762714, 127879953, 1349693257, 2077116967, 3663030929, 3408827113, 1685957243, 45074849, 2300292735, 4043955814, 1539297202, 2027447957, 771978288, 1337044258, 1717809472
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
