/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1492701695, 384069836, 1699699893, 1687211928, 712038993, 435733444, 559580201, 1652936302, 176234948, 2074961999, 1186828884, 1514498779, 1415784169, 1934906697, 722766724, 3949551621
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2797477476, 2678034166, 2206351465, 1407647672, 1489485295, 949556259, 4235932841, 3176489396, 312124164, 2731376482, 3615182330, 1645086124, 2290000832, 3375007675, 3145994411, 252291994
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    bool8_t masked[] = {
    0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1
    };
    const bool8_t *mask = &masked[0];
    vuint32m4_t data1_v = __riscv_vle32_v_u32m4 (in1, vl);
    vuint32m4_t data2_v = __riscv_vle32_v_i32m4 (in2, vl);
    vuint32m4_t out_v = __riscv_vle32_v_u32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_u32m4 (uint32_t *out, vuint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    4290179171, 3062104002, 3906051359, 3094859600, 2201524289, 1385289703, 4795513043, 4829425698, 488359113, 4806338482, 4802011215, 3159584903, 3705785001, 5309914373, 3868761136, 4201843616
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
