/* { dg-do run } */
/* { dg-options "-march=rv64gcv -mabi=lp64d -O3 -fno-schedule-insns -fno-schedule-insns2" } */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "riscv_vector.h"
int main(){
    vint32m2_t data1[] = {
    342718547, 3382920792, 3358116013, 3449170660, 3996314251, 1066184255, 2468339108, 2118545126
    };
    const vint32m2_t *in1 = &data1[0];
    vint32m2_t data2[] = {
    840575083, 1841247314, 1099869601, 920424675, 2852194579, 2545866388, 213159397, 2232850394
    };
    const vint32m2_t *in2 = &data2[0];
    vint32m2_t out_data[64];
    vint32m2_t *out = &out_data[0];
    for (int n = 8, Q_element = 32;n >= 0; n -= Q_element) {
        vint32m2_t out = __riscv_vadd_vx_i32m2 (data1, data2, 64);
        in1 += Q_element;
        in2 += Q_element;
        out += Q_element;
      }
    vint32m2_t golden[] = {
    1183293630, 5224168106, 4457985614, 4369595335, 6848508830, 3612050643, 2681498505, 4351395520
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
