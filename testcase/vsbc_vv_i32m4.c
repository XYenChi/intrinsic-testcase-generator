/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    909913109, 1697051043, 2696069553, 2941324824, 702517183, 3865807328, 2739747148, 383473400, 2316640989, 253722228, 2338258069, 560365736, 3132992058, 2695919504, 1830658208, 3175062511
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    4026739650, 1072186210, 3152206017, 351752818, 2513149014, 4102239617, 2187664043, 586958262, 1747545333, 634664157, 859495035, 1064128478, 2706857071, 4063987635, 3958696593, 1652393417
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e32m4(size_t avl);
    const int32_t out_data[16];
    const int32_t *out = &out_data[0];
    vint32m4_t data1_v = __riscv_vle32_v_i32m4 (*in1, vl);
    vint32m4_t data2_v = __riscv_vle32_v_i32m4 (*in2, vl);
    vint32m4_t out_v = __riscv_vle32_v_i32m4 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vsbc_vv_i32m4 (data1_v, data2_v, vl);
        void vint32m4_t __riscv_vse32_v_i32 (int32m4_t *out, out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
      }
    int32_t golden[] = {
    -3116826541, 624864833, -456136464, 2589572006, -1810631831, -236432289, 552083105, -203484862, 569095656, -380941929, 1478763034, -503762742, 426134987, -1368068131, -2128038385, 1522669094
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
