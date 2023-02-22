/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint64m2_t data1[] = {
    3166072713365757034, 5120850702789385297, 723601219365475896, 17610643883537103192
    };
    const vint64m2_t *in1 = &data1[0];
    vint64m2_t data2[] = {
    3309767453170024296, 11454167126503783495, 11361461318172861479, 11209000602209288818
    };
    const vint64m2_t *in2 = &data2[0];
    vint64m2_t out_data[64];
    vint64m2_t *out = &out_data[0];
    for (int n = 4, Q_element = 64;n >= 0; n -= Q_element) {
        vint64m2_t out = __riscv_vadd_vx_i64m2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint64m2_t golden[] = {
    6475840166535781330, 16575017829293168792, 12085062537538337375, 28819644485746392010
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
