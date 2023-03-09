/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2 -w" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    const int32_t data1[] = {
    -860128449, 1001778262, 1612913698, -145521978, 2027587352, -30842065, 1400541294, 551107679, -1830556777, -247610679, -1220551193, -1196827848, -905841145, -1019537612, 1093788569, -1978093615
    };
    const int32_t *in1 = &data1[0];
    const int32_t data2[] = {
    -505046604, 171869020, 471838274, 1776765869, -453261730, -1421533965, -1427915854, 149541978, -1716400263, 425750105, -1715142013, -21121285, 294944295, -380742028, 1872229332, 1085883239
    };
    const int32_t *in2 = &data2[0];
    size_t avl = 64;
    size_t vl = __riscv_vsetvl_e32mf2(avl);
    bool64_t masked[] = {
    1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 0, 1
    };
    const bool64_t *mask = &masked[0];
    vint32mf2_t data1_v = __riscv_vle32_v_i32mf2 (in1, vl);
    vint32mf2_t data2_v = __riscv_vle32_v_i32mf2 (in2, vl);
    vint32mf2_t out_v = __riscv_vle32_v_i32mf2 (out, vl);
    for (size_t n = 0; n < vl; n++) {
        void __riscv_vse32_v_i32mf2 (int32_t *out, vint32mf2_t out_v, size_t vl);
        in1 += 4;
        in2 += 4;
        out += 4;
        mask += 4;
      }
    int32_t golden[] = {
    -1365175052, 1173647283, 2084751973, 1631243891, 1574325623, -1452376029, -27374560, 700649657, -3546957039, 178139426, -2935693205, -1217949133, -610896849, -1400279640, 2966017901, -892210375
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
