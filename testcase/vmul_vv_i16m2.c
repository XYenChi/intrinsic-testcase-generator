/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    26933, 40731, 62181, 40803, 46475, 15939, 61984, 40057, 43708, 59291, 32490, 53071, 43396, 64966, 23166, 3605
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    63018, 33181, 42213, 45028, 10208, 26365, 45296, 18230, 26790, 137, 17723, 2110, 64200, 26629, 58207, 36630
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16m2(size_t avl);
    const int16_t out_data[16];
    const int16_t *out = &out_data[0];
    vint16m2_t data1_v = __riscv_vle16_v_i16m2 (*in1, vl);
    vint16m2_t data2_v = __riscv_vle16_v_i16m2 (*in2, vl);
    vint16m2_t out_v = __riscv_vle16_v_i16m2 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vv_i16m2 (data1_v, data2_v, vl);
        void vint16m2_t __riscv_vse16_v_i16 (int16m2_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
      }
    int16_t golden[] = {
    1697263794, 1351495311, 2624846553, 1837277484, 474416800, 420231735, 2807627264, 730239110, 1170937320, 8122867, 575820270, 111979810, 2786023200, 1729979614, 1348423362, 132051150
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
