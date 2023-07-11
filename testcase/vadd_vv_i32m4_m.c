/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1755662764, 804635407, 1226794944, 270655198, 2011890467, 1900804017, -977166203, -913889024, 1287395576, 726182839, -1823662095, 1889988782, 300588777, -8892204, -591137885, -1141456592
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1052355580, 1818548629, -798361175, 1259807583, 694899746, 246296538, -1776641175, 1954746579, -489518842, -129553321, 1248569307, 2067488152, 660075319, -1649517295, 839574944, 1797062456
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32m4(avl);
    const int out_data[] = {
    1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0
    };
    const int32_t *out = &out_data[0];
    uint8_t masked[] = {
    0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0
    };
    const uint8_t *mask = &masked[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32m4 (int32_t *out, vint32m4_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    1, 2623184036, 1, 1530462781, 0, 0, 1, 1, 0, 596629518, 1, 1, 1, 2636557797, 1, 0
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
