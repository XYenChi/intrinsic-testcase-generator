/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    515843699, 3550951619, 4008081600, 1046530925, 4002286821, 2119307344, 873181000, 4193442697, 2786255242, 466478698, 2314115685, 267104908, 810153812, 2262059298, 721887793, 3942172548
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    1206099242, 365355538, 3452015678, 2702354495, 3818324647, 253286056, 738793248, 278059254, 2152020943, 177230795, 506508182, 2456710630, 2782562436, 1734293587, 1075073686, 348978937
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m8(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m8_t data1_v = __riscv_vle32_v_i32m8 (*in1, vl);
    vint32m8_t data2_v = __riscv_vle32_v_i32m8 (*in2, vl);
    vint32m8_t out_v = __riscv_vle32_v_i32m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmin_vv_i32m8 (data1_v, data2_v, vl);
        void vint32m8_t __riscv_vse32_v_i32 (int32m8_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    1206099242, 3550951619, 4008081600, 2702354495, 4002286821, 2119307344, 873181000, 4193442697, 2786255242, 466478698, 2314115685, 2456710630, 2782562436, 2262059298, 1075073686, 3942172548
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
