/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    22245, 40710, 5103, 52270, 41853, 53829, 20384, 8899, 12812, 49905, 52435, 52187, 59920, 25029, 62714, 48283
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    14370, 56713, 35289, 6500, 44781, 36121, 21314, 52133, 14996, 41407, 59377, 15965, 17503, 9721, 37168, 19981
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m1(size_t avl);
    const int out_data[] = {
    55799, 32450, 17628, 4455, 29752, 1896, 41062, 42584, 15406, 32683, 60739, 10545, 21541, 50436, 652, 59396
    };
    const int16_t *out = &out_data[0];
    bool16_t masked[] = {
    1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0
    };
    const bool16_t *mask = &masked[0];
    vint16m1_t data1_v = __riscv_vle16_v_i16m1_m (mask, *in1, vl);
    vint16m1_t data2_v = __riscv_vle16_v_i16m1_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i16m1_m (mask, data1_v, data2_v, vl);
        void vint16_t __riscv_vse16m1_v_i16 (vbool16_t mask, int16m1_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    319660650, 2308786230, 180079767, 339755000, 29752, 1896, 41062, 463931567, 192128752, 32683, 60739, 10545, 1048779760, 243306909, 2330953952, 59396
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
