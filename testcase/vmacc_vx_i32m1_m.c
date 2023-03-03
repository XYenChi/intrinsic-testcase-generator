/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    3645860345, 860601061, 1188627989, 3794432191, 2995290888, 449404224, 807351666, 2145955886, 3518114056, 4267829801, 1691159715, 1538458739, 1920149417, 2345945029, 2825761802, 103170671
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    2363894167, 2826694587, 3346580963, 3461155511, 95806457, 2633806847, 4196583838, 3026660546, 2698839775, 2424767994, 95815006, 2124301717, 3290531940, 3512901255, 1539011334, 2378170354
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m1(size_t avl);
    const int out_data[] = {
    4098010246, 1704443005, 3930367101, 4286708086, 1176577682, 197089382, 348517590, 4039294112, 1349245082, 4140799400, 1299961761, 470131949, 77825831, 1370541076, 3018565678, 926607823
    };
    const int32_t *out = &out_data[0];
    bool32_t masked[] = {
    0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0
    };
    const bool32_t *mask = &masked[0];
    vint32m1_t data1_v = __riscv_vle32_v_i32m1_m (mask, *in1, vl);
    vint32m1_t data2_v = __riscv_vle32_v_i32m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i32m1_m (mask, data1_v, data2_v, vl);
        void vint32_t __riscv_vse32m1_v_i32 (vbool32_t mask, int32m1_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    14940773049295094870, 1466845458517028306, 4671744343293389890, 16265623154938396427, 3524192409918761616, 88572800776349569, 281376256916804941, 8668146974931543233, 4746798087973072592, 17672227079282919401, 2198442961243658116, 723278605422152312, 149437224022190528, 3215214024282511205, 8529747589720631756, 95598750852759233
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
