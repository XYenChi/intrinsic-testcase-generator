/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    27907, 17766, 50981, 41812, 28635, 9056, 34893, 35228, 23430, 48698, 9512, 48682, 24684, 33803, 46824, 9892
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    30868, 57012, 65103, 35047, 50073, 15936, 60549, 51544, 23277, 24786, 11106, 60657, 11114, 16772, 15889, 41112
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    31258, 9801, 11451, 18944, 55836, 48128, 30347, 31203, 41635, 51796, 28493, 56515, 31669, 13053, 29901, 9198
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmul_vx_i16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    31258, 1012875192, 3319016043, 1465385164, 55836, 48128, 30347, 1815792032, 41635, 51796, 105640272, 56515, 274337976, 13053, 29901, 9198
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
