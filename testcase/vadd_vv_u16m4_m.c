/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int16_t data1[] = {
    12100, 12032, -28679, 13895, 19532, -9167, 13098, -14765, 21221, 7884, 22219, 20176, -20145, 1611, 13494, -24060
    };
    const int16_t *in1 = &data1[0];
    const int16_t data2[] = {
    24740, -1201, -28456, 13369, 19597, -30171, -3436, -11629, -21967, -27049, 2615, -14010, 25530, 1340, -9012, -10611
    };
    const int16_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e16m4(avl);
    const int out_data[] = {
    4597, -16591, -26726, -20740, -3047, -6087, 22784, -7088, -24887, 31628, -22186, 25978, -1744, 18199, 26123, 6612
    };
    const int16_t *out = &out_data[0];
    bool4_t masked[] = {
    1, 0, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0
    };
    const bool4_t *mask = &masked[0];
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *in1, vl);
    vint16m4_t data2_v = __riscv_vle16_v_i16m4_m (mask, *in2, vl);
    vint16m4_t data1_v = __riscv_vle16_v_i16m4_m (mask, *out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vadd_vv_u16m4_m (mask, data1_v, data2_v, vl);
        void __riscv_vse16_v_i16m4 (bool16_t mask, int16_t *out, vint16m4_t out_v, size_t vl);
        in1 += 2;
        in2 += 2;
        out += 2;
        mask += 2;
      }
    int16_t golden[] = {
    4598, -16591, -26725, -20740, -3046, -6086, 22785, -7088, -24887, 31629, -22186, 25978, -1744, 18200, 26124, 6612
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
