/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    2256969811, 537315723, 2570102458, 4274699720, 3555328492, 947468444, 3085461982, 641031937, 1141996149, 2278749946, 3767958142, 1571700386, 2017090483, 1507232006, 780299970, 3443963080
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    4229459322, 2675813479, 3031739667, 1128295182, 2464603378, 2892725963, 3629283555, 4275221039, 3035035785, 1828567780, 1240144286, 1459176059, 4016176216, 2654372587, 2272565533, 3992972220
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m2(size_t avl);
    const int out_data[] = {
    624991008, 2574473360, 2123470196, 3388716122, 536648228, 1112459074, 4178923581, 3554328145, 2777653183, 36627973, 2894620310, 3484886585, 640583975, 3027657024, 955184209, 1963411090
    };
    const int32_t *out = &out_data[0];
    bool16_t masked[] = {
    0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2_m (mask, *in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        void vint16_t __riscv_vse32m2_v_i32 (vbool32_t mask, int32m2_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    6486429133, 3213129203, 5601842125, 5402994902, 6019931871, 3840194407, 6714745538, 4916252977, 4177031934, 4107317726, 5008102429, 3030876446, 6033266699, 4161604593, 3052865504, 7436935300
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
