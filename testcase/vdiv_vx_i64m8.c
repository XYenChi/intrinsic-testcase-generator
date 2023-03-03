/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int64_t data1[] = {
    7189477545737277123, 5723252927661853076, 17331992208833486130, 3138398418563432021, 5308366850751747382, 1458308427304974880, 5851395665048639177, 1665739680009843444, 9676434009330832495, 869835166808715934, 778235802487518415, 2593909322165261245, 14626101038353852214, 8004999174717386965, 1540739502716383920, 9471152716540371442
    };
    const int64_t *in1 = &data1[0];
    const int64_t data2[] = {
    2268884568338560535, 465678428073007764, 2350004443283120416, 14361118249191729571, 17234222719785853786, 183258397317948664, 17663499995602981062, 501662853584269885, 7121446694942625375, 2076747116416200557, 18141341918485522287, 15693437557905883807, 16710905585918336686, 11873558105568589405, 11411659885808249466, 10100918034542372027
    };
    const int64_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = vsetvl_e64m8(size_t avl);
    const int64_t out_data[16];
    const int64_t *out = &out_data[0];
    vint64m8_t data1_v = __riscv_vle64_v_i64m8 (*in1, vl);
    vint64m8_t data2_v = __riscv_vle64_v_i64m8 (*in2, vl);
    vint64m8_t out_v = __riscv_vle64_v_i64m8 (*out, vl);
    for (size_t n = 0; n < vl; n++) {
        out_v = __riscv_vdiv_vx_i64m8 (data1_v, data2_v, vl);
        void vint64m8_t __riscv_vse64_v_i64 (int64m8_t *out, out_v, size_t vl);
        in1 += 8;
        in2 += 8;
        out += 8;
      }
    int64_t golden[] = {
    0, 0, 0, 4, 3, 0, 3, 0, 0, 2, 23, 6, 1, 1, 7, 1
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
