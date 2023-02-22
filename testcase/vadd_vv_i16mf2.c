/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint16mf2_t data1[] = {
    157, 41091, 32822, 2761
    };
    const vint16mf2_t *in1 = &data1[0];
    vint16mf2_t data2[] = {
    4605, 10354, 6373, 54230
    };
    const vint16mf2_t *in2 = &data2[0];
    vint16mf2_t out_data[64];
    vint16mf2_t *out = &out_data[0];
    for (int n = 4, Q_element = 16;n >= 0; n -= Q_element) {
        vint16mf2_t out = __riscv_vadd_vv_i16mf2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint16mf2_t golden[] = {
    4762, 51445, 39195, 56991
    };
    int fail = 0;
    for (int i = 0; i < 4; i++){
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
