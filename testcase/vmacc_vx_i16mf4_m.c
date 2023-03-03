/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    6965, 29198, 29688, 40373, 32114, 7222, 7483, 52788, 14731, 46287, 12379, 17711, 12366, 386, 1178, 8887
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    10930, 20438, 9963, 48926, 40157, 50344, 60107, 47948, 22111, 46760, 43603, 21642, 5765, 44748, 61213, 15698
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e16mf4(size_t avl);
    const int out_data[] = {
    41374, 24947, 11092, 40851, 40578, 13368, 32954, 11181, 42384, 7538, 54984, 14054, 36464, 59010, 29579, 42041
    };
    const int16_t *out = &out_data[0];
    bool64_t masked[] = {
    1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint16mf4_t data1_v = __riscv_vle16_v_i16mf4_m (mask, *in1, vl);
    vint16mf4_t data2_v = __riscv_vle16_v_i16mf4_m (mask, *in2, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vmacc_vx_i16mf4_m (mask, data1_v, data2_v, vl);
        void vint64_t __riscv_vse16mf4_v_i16 (vbool16_t mask, int16mf4_t *out, out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    288169911, 728402507, 329299296, 1649277423, 1303121893, 96543697, 246594782, 590222628, 624358704, 348911407, 680646937, 248910394, 450913824, 22777860, 34844062, 373618368
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
