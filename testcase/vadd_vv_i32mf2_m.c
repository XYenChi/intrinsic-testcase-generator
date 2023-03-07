/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -1825334324, -127855785, -795513901, 1714696335, 121623063, -1735472589, 971626741, 527193009, -700195837, -18025216, -255743771, -1255567538, -2051660827, -908295772, 440723505, 1363806855
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    394490123, 738921011, 14612011, -1194743967, 1509832578, -1727800091, 2073093512, 2079205148, -2049279611, 81678340, 2107246777, 57334652, 1166434861, 1785544419, -1180842848, -577169368
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    const int out_data[] = {
    -2126838181, -1781026460, -694745128, -445410875, -2050631747, 221775127, -481435667, -924950580, -1727381946, -1611111590, -62373419, 1115125444, -585981608, -1222919536, 1482107594, 227812411
    };
    const int32_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 0, 1, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2_m (mask, *in2, vl);
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_i32mf2_m (mask, data1_v, data2_v, vl);
        void __riscv_vse32_v_i32mf2 (bool32_t mask, int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -2126838181, -1781026460, -694745127, -445410874, -2050631747, 221775128, -481435667, -924950580, -1727381945, -1611111590, -62373418, 1115125444, -585981607, -1222919535, 1482107594, 227812412
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
