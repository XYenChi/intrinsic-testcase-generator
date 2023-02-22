/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m4_t data1[] = {
    17927537703709236051, 4208915064597063261, 9725174921038575942, 16175042830240795775, 17604477138452271534, 18053595988850071383, 14794335429530940203, 571765834507120510
    };
    const vint64m4_t *in1 = &data1[0];
    vint64m4_t data2[] = {
    7862914418355633727, 15518186916719428077, 1960415597583887555, 16336443505546653144, 14645587125499539344, 7830413626196079437, 14486585749478381534, 2903926759097146725
    };
    const vint64m4_t *in2 = &data2[0];
    vint64m4_t out_data[64];
    vint64m4_t *out = &out_data[0];
    for (int n = 8, Q_element = 64;n >= 0; n -= Q_element) {
        vint64m4_t out = __riscv_vadd_vx_i64m4 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint64m4_t golden[] = {
    25790452122064869778, 19727101981316491338, 11685590518622463497, 32511486335787448919, 32250064263951810878, 25884009615046150820, 29280921179009321737, 3475692593604267235
    };
    int fail = 0;
    for (int i = 0; i < 8; i++){
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
