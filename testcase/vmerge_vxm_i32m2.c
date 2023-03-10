/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    1693344815, 932629955, 99243364, -880828084, -642761393, 1925259032, -1662606264, 1798543609, -328759978, 563416847, 1616691641, -1358314707, -887500774, 109877421, 1395350662, 1415293022
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -2049812083, -1911908215, -592768211, -979192383, -93301983, -2021897975, -965213509, -1123603668, -1988531817, 427847495, 1202672897, -98566189, 253195515, -1721612480, -3056965, 548967004
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m2(avl);
    bool16_t masked[] = {
    1, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1
    };
    const bool16_t *mask = &masked[0];
    vint32m2_t data1_v = __riscv_vle32_v_i32m2 (in1, vl);
    vint32m2_t data2_v = __riscv_vle32_v_i32m2 (in2, vl);
    vint32m2_t out_v = __riscv_vle32_v_i32m2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m2 (int32_t *out, vint32m2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -2049812083, 932629955, 99243364, -880828084, -93301983, -2021897975, -1662606264, 1798543609, -1988531817, 563416847, 1616691641, -98566189, -887500774, 109877421, -3056965, 548967004
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
